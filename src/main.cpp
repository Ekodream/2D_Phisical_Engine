#include <iostream>
#include <chrono>
#include "core/Math/Vector2.h"
#include "core/Physics/Body.h"

#ifdef ENABLE_SFML
#include "render/Renderer.h"
#endif

int main() {
    std::cout << "2D Physical Engine - Phase 1\n";

#ifdef ENABLE_SFML
    // ===== SFML-enabled mode: interactive GUI =====
    std::cout << "Running with SFML renderer.\n";
    engine::Renderer renderer(1024, 768, "2D Physics Engine");

    // Create test objects
    engine::PointMass ball1({100.0, 100.0}, {100.0, 50.0}, 1.0);
    engine::PointMass ball2({500.0, 400.0}, {-50.0, 100.0}, 2.0);

    // Physics parameters
    const double dt = 1.0 / 60.0;  // 60 FPS
    const engine::Vector2 gravity(0.0, 500.0);  // pixels/s^2 downward

    double elapsed = 0.0;

    while (renderer.isOpen()) {
        renderer.handleEvents();

        // Update physics
        ball1.applyForce(engine::Vector2(0.0, ball1.mass * gravity.y), dt);
        ball2.applyForce(engine::Vector2(0.0, ball2.mass * gravity.y), dt);

        ball1.integrate(dt);
        ball2.integrate(dt);

        elapsed += dt;

        // Boundary conditions (bounce off edges)
        if (ball1.position.y > 700) {
            ball1.position.y = 700;
            ball1.velocity.y *= -0.8;  // Inelastic bounce
        }
        if (ball2.position.y > 700) {
            ball2.position.y = 700;
            ball2.velocity.y *= -0.8;
        }

        // Render
        renderer.clear();
        renderer.drawPointMass(ball1, 8.0, sf::Color::Green);
        renderer.drawVelocityVector(ball1, 0.1, sf::Color::Red);

        renderer.drawPointMass(ball2, 10.0, sf::Color::Yellow);
        renderer.drawVelocityVector(ball2, 0.1, sf::Color::Cyan);

        // Draw floor
        renderer.drawLine(engine::Vector2(0, 700), engine::Vector2(1024, 700), sf::Color::White);

        renderer.drawText("ESC to quit | Phase 1: Basic physics", 10, 10, sf::Color::White);

        renderer.display();
    }

#else
    // ===== Non-SFML mode: simple numerical output =====
    std::cout << "Running without SFML (non-visual mode).\n";
    std::cout << "Compile with -DUSE_SFML=ON for interactive rendering.\n\n";

    engine::PointMass p({0.0, 0.0}, {1.0, 0.0}, 1.0);
    engine::Vector2 gravity(0.0, 9.8);

    for (int i = 0; i < 10; ++i) {
        p.applyForce(gravity * p.mass, 0.1);
        p.integrate(0.1);
        std::cout << "Step " << i << ": pos=(" << p.position.x << ", " << p.position.y << "), "
                  << "vel=(" << p.velocity.x << ", " << p.velocity.y << ")\n";
    }
#endif

    return 0;
}
