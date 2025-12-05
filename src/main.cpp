#include <iostream>
#include <chrono>
#include "core/Math/Vector2.h"
#include "core/Physics/Body.h"
#include "core/Physics/Collision.h"
#include "render/Renderer.h"

int main() {
    std::cout << "2D Physical Engine - Phase 1\n";

    // ===== SFML-enabled mode: interactive GUI (SFML is required) =====
    std::cout << "Running with SFML renderer.\n";
    engine::Renderer renderer(1024, 768, "2D Physics Engine");
    // Interactive objects container
    std::vector<engine::PointMass> objects;

    // Interaction parameters (adjustable)
    double current_radius = 8.0;
    double current_restitution = 0.8;
    int selectedIndex = -1;

    // Physics parameters
    const double dt = 1.0 / 60.0;  // 60 FPS
    const engine::Vector2 gravity(0.0, 500.0);  // pixels/s^2 downward

    bool paused = false;

    // Spawn a couple default objects
    objects.emplace_back(engine::Vector2(150.0, 80.0), engine::Vector2(40.0, 20.0), 1.0);
    objects.emplace_back(engine::Vector2(480.0, 120.0), engine::Vector2(-20.0, 10.0), 2.0);

    while (renderer.isOpen()) {
        renderer.handleEvents();

        // Process input events
        while (true) {
            auto evOpt = renderer.pollInput();
            if (!evOpt.has_value()) break;
            auto ev = *evOpt;
            if (ev.type == engine::Renderer::InputType::MouseClick) {
                // Right-click: select nearest object; Left-click: spawn
                if (ev.mouseButton == static_cast<int>(sf::Mouse::Button::Right)) {
                    // select nearest within threshold
                    double bestDist2 = 1e9;
                    int bestIdx = -1;
                    for (size_t i = 0; i < objects.size(); ++i) {
                        double dx = objects[i].position.x - ev.pos.x;
                        double dy = objects[i].position.y - ev.pos.y;
                        double d2 = dx*dx + dy*dy;
                        if (d2 < bestDist2) { bestDist2 = d2; bestIdx = (int)i; }
                    }
                    if (bestIdx != -1 && bestDist2 <= (30.0*30.0)) {
                        selectedIndex = bestIdx;
                        // optionally apply current params immediately
                        objects[selectedIndex].radius = current_radius;
                        objects[selectedIndex].restitution = current_restitution;
                    } else {
                        selectedIndex = -1;
                    }
                } else {
                    // Left-click spawn point mass at click (zero initial velocity)
                    double mass = std::max(0.1, current_radius * 0.1);
                    objects.emplace_back(engine::Vector2(ev.pos.x, ev.pos.y), engine::Vector2(0.0, 0.0), mass, current_radius, current_restitution);
                }
            } else if (ev.type == engine::Renderer::InputType::MouseDrag) {
                // spawn with initial velocity proportional to drag vector (release - start)
                engine::Vector2 dv = ev.pos2 - ev.pos;
                double speedScale = 2.0; // tune for visible speed
                engine::Vector2 initVel = dv * speedScale;
                double mass = std::max(0.1, current_radius * 0.1);
                objects.emplace_back(engine::Vector2(ev.pos.x, ev.pos.y), initVel, mass, current_radius, current_restitution);
            } else if (ev.type == engine::Renderer::InputType::KeyPressed) {
                // Controls:
                // Space: pause/resume
                // R/F: radius + / -
                // T/G: restitution + / -
                if (ev.key == static_cast<int>(sf::Keyboard::Key::Space)) {
                    paused = !paused;
                } else if (ev.key == static_cast<int>(sf::Keyboard::Key::R)) {
                    current_radius += 1.0;
                    if (current_radius < 1.0) current_radius = 1.0;
                    if (selectedIndex >= 0) objects[selectedIndex].radius = current_radius;
                } else if (ev.key == static_cast<int>(sf::Keyboard::Key::F)) {
                    current_radius -= 1.0;
                    if (current_radius < 1.0) current_radius = 1.0;
                    if (selectedIndex >= 0) objects[selectedIndex].radius = current_radius;
                } else if (ev.key == static_cast<int>(sf::Keyboard::Key::T)) {
                    current_restitution += 0.05;
                    if (current_restitution > 1.0) current_restitution = 1.0;
                    if (selectedIndex >= 0) objects[selectedIndex].restitution = current_restitution;
                } else if (ev.key == static_cast<int>(sf::Keyboard::Key::G)) {
                    current_restitution -= 0.05;
                    if (current_restitution < 0.0) current_restitution = 0.0;
                    if (selectedIndex >= 0) objects[selectedIndex].restitution = current_restitution;
                }
            }
        }

        // Update physics when not paused
        if (!paused) {
            for (auto &obj : objects) {
                obj.applyForce(engine::Vector2(0.0, obj.mass * gravity.y), dt);
                obj.integrate(dt);
            }

            // Resolve collisions (pairwise)
            for (size_t i = 0; i < objects.size(); ++i) {
                for (size_t j = i + 1; j < objects.size(); ++j) {
                    engine::resolveCircleCollision(objects[i], objects[j]);
                }
            }

            // Simple floor bounce after collision resolution
            for (auto &obj : objects) {
                if (obj.position.y > 700) {
                    obj.position.y = 700;
                    obj.velocity.y *= -1;
                }
            }
        }

        // Render
        renderer.clear();

        // Draw objects
        for (size_t i = 0; i < objects.size(); ++i) {
            const auto &obj = objects[i];
            sf::Color col = (selectedIndex == (int)i) ? sf::Color::Yellow : sf::Color::Green;
            renderer.drawPointMass(obj, obj.radius, col);
            renderer.drawVelocityVector(obj, 0.08, sf::Color::Red);
            // If selected, draw outline to show radius
            if (selectedIndex == (int)i) {
                renderer.drawCircleOutline(obj.position, obj.radius + 2.0, sf::Color::Yellow, 2.0f);
            }
        }

        // Draw floor and UI text
        renderer.drawLine(engine::Vector2(0, 700), engine::Vector2(1024, 700), sf::Color::White);
        char buf[200];
        sprintf(buf, "Click L: spawn | Drag: spawn w/vel | R/F: radius +/- (%.1f) | T/G: restitution +/- (%.2f)", current_radius, current_restitution);
        renderer.drawText(buf, 10, 10, sf::Color::White);

        if (paused) renderer.drawText("PAUSED", 900, 10, sf::Color::Yellow);

        if (selectedIndex >= 0) {
            char s[100];
            sprintf(s, "Selected: idx=%d r=%.1f e=%.2f", selectedIndex, objects[selectedIndex].radius, objects[selectedIndex].restitution);
            renderer.drawText(s, 10, 30, sf::Color::Yellow);
        }

        renderer.display();
    }

    return 0;
}
