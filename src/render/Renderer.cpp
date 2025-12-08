//This part is finished with the help of the official documents and AI
#include "Renderer.h"
#include <iostream>
#include <cmath>
#include <filesystem>
#include <optional>

namespace engine {

Renderer::Renderer(int width, int height, const char* title)
    : windowWidth(width), windowHeight(height) {
    window = std::make_unique<sf::RenderWindow>(
        sf::VideoMode(sf::Vector2u(static_cast<unsigned int>(width), static_cast<unsigned int>(height))),
        sf::String(title)
    );
    window->setFramerateLimit(60);
    loadFont();
}

Renderer::~Renderer() {
    if (window) {
        window->close();
    }
}

bool Renderer::loadFont() {
    // Attempt to load a system font (Windows)
    // On Windows, common paths: C:/Windows/Fonts/
    std::vector<std::string> fontPaths = {
        "C:/Windows/Fonts/arial.ttf",
        "C:/Windows/Fonts/Arial.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf"
    };

    for (const auto& path : fontPaths) {
        try {
            if (font.openFromFile(std::filesystem::path(path))) {
                return true;
            }
        } catch (...) {
            // ignore
        }
    }

    std::cout << "Warning: could not load any system font; text rendering disabled.\n";
    return false;
}

void Renderer::clear() {
    if (window) {
        window->clear(sf::Color::Black);
    }
}

void Renderer::display() {
    if (window) {
        window->display();
    }
}

void Renderer::handleEvents() {
    if (!window) return;

    while (const std::optional<sf::Event> eventOpt = window->pollEvent()) {
        const sf::Event& event = *eventOpt;
        if (event.is<sf::Event::Closed>()) {
            window->close();
            continue;
        }

        if (event.is<sf::Event::KeyPressed>()) {
            if (const auto* kp = event.getIf<sf::Event::KeyPressed>()) {
                // Close on Escape
                if (kp->code == sf::Keyboard::Key::Escape) {
                    window->close();
                    continue;
                }
                // Queue key event
                InputEvent ie;
                ie.type = InputType::KeyPressed;
                ie.key = static_cast<int>(kp->code);
                inputQueue.push_back(ie);
            }
            continue;
        }

        if (event.is<sf::Event::MouseButtonPressed>()) {
            if (const auto* mp = event.getIf<sf::Event::MouseButtonPressed>()) {
                mouseDownPos = engine::Vector2(static_cast<double>(mp->position.x), static_cast<double>(mp->position.y));
                mouseDown = true;
                mouseDownButton = static_cast<int>(mp->button);
            }
            continue;
        }

        if (event.is<sf::Event::MouseButtonReleased>()) {
            if (const auto* mr = event.getIf<sf::Event::MouseButtonReleased>()) {
                engine::Vector2 upPos(static_cast<double>(mr->position.x), static_cast<double>(mr->position.y));
                if (mouseDown) {
                    InputEvent ie;
                    // If the drag distance is small, treat as click
                    const double dx = upPos.x - mouseDownPos.x;
                    const double dy = upPos.y - mouseDownPos.y;
                    const double dist2 = dx*dx + dy*dy;
                    if (dist2 < 4.0) {
                        ie.type = InputType::MouseClick;
                        ie.pos = upPos;
                    } else {
                        ie.type = InputType::MouseDrag;
                        ie.pos = mouseDownPos;
                        ie.pos2 = upPos;
                    }
                    ie.mouseButton = mouseDownButton;
                    inputQueue.push_back(ie);
                }
                mouseDown = false;
                mouseDownButton = -1;
            }
            continue;
        }
    }
}

std::optional<Renderer::InputEvent> Renderer::pollInput() {
    if (inputQueue.empty()) return std::nullopt;
    InputEvent ie = inputQueue.front();
    inputQueue.erase(inputQueue.begin());
    return ie;
}

void Renderer::drawCircle(const Vector2& center, double radius, const sf::Color& color) {
    if (!window) return;

    sf::CircleShape circle(static_cast<float>(radius));
    circle.setPosition(sf::Vector2f(static_cast<float>(center.x - radius),
                                    static_cast<float>(center.y - radius)));
    circle.setFillColor(color);
    window->draw(circle);
}

void Renderer::drawRect(const Vector2& pos, double width, double height, const sf::Color& color) {
    if (!window) return;

    sf::RectangleShape rect(sf::Vector2f(static_cast<float>(width), static_cast<float>(height)));
    rect.setPosition(sf::Vector2f(static_cast<float>(pos.x), static_cast<float>(pos.y)));
    rect.setFillColor(color);
    window->draw(rect);
}

void Renderer::drawLine(const Vector2& from, const Vector2& to, const sf::Color& color) {
    if (!window) return;

    sf::Vertex line[2];
    line[0].position = sf::Vector2f(static_cast<float>(from.x), static_cast<float>(from.y));
    line[0].color = color;
    line[1].position = sf::Vector2f(static_cast<float>(to.x), static_cast<float>(to.y));
    line[1].color = color;
    window->draw(line, 2, sf::PrimitiveType::Lines);
}

void Renderer::drawText(const std::string& text, float x, float y, const sf::Color& color) {
    if (!window) return;

    // SFML 3: constructor signature is (const sf::Font&, sf::String, unsigned int)
    sf::Text sfText(font, sf::String(text), 14u);
    sfText.setPosition(sf::Vector2f(x, y));
    sfText.setFillColor(color);
    window->draw(sfText);
}

void Renderer::drawPointMass(const PointMass& p, double radius, const sf::Color& color) {
    drawCircle(p.position, radius, color);
}

void Renderer::drawVelocityVector(const PointMass& p, double scale, const sf::Color& color) {
    Vector2 endPos = p.position + p.velocity * scale;
    drawLine(p.position, endPos, color);

    // Draw arrowhead (simple version: small circle at end)
    drawCircle(endPos, 2.0, color);
}

void Renderer::drawCircleOutline(const Vector2& center, double radius, const sf::Color& color, float thickness) {
    if (!window) return;
    sf::CircleShape circle(static_cast<float>(radius));
    circle.setPosition(sf::Vector2f(static_cast<float>(center.x - radius), static_cast<float>(center.y - radius)));
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineThickness(thickness);
    circle.setOutlineColor(color);
    window->draw(circle);
}

}
