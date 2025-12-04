#include "Renderer.h"
#include <iostream>
#include <cmath>

#ifdef ENABLE_SFML

namespace engine {

Renderer::Renderer(int width, int height, const char* title)
    : windowWidth(width), windowHeight(height) {
    window = std::make_unique<sf::RenderWindow>(
        sf::VideoMode(width, height),
        title
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
        if (font.loadFromFile(path)) {
            return true;
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

    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                window->close();
            }
        }
    }
}

void Renderer::drawCircle(const Vector2& center, double radius, const sf::Color& color) {
    if (!window) return;

    sf::CircleShape circle(static_cast<float>(radius));
    circle.setPosition(
        static_cast<float>(center.x - radius),
        static_cast<float>(center.y - radius)
    );
    circle.setFillColor(color);
    window->draw(circle);
}

void Renderer::drawRect(const Vector2& pos, double width, double height, const sf::Color& color) {
    if (!window) return;

    sf::RectangleShape rect(sf::Vector2f(static_cast<float>(width), static_cast<float>(height)));
    rect.setPosition(static_cast<float>(pos.x), static_cast<float>(pos.y));
    rect.setFillColor(color);
    window->draw(rect);
}

void Renderer::drawLine(const Vector2& from, const Vector2& to, const sf::Color& color) {
    if (!window) return;

    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(static_cast<float>(from.x), static_cast<float>(from.y)), color),
        sf::Vertex(sf::Vector2f(static_cast<float>(to.x), static_cast<float>(to.y)), color)
    };
    window->draw(line, 2, sf::Lines);
}

void Renderer::drawText(const std::string& text, float x, float y, const sf::Color& color) {
    if (!window) return;

    sf::Text sfText(text, font);
    sfText.setPosition(x, y);
    sfText.setFillColor(color);
    sfText.setCharacterSize(14);
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

} // namespace engine

#endif
