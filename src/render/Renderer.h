#pragma once

#ifdef ENABLE_SFML
#include <SFML/Graphics.hpp>
#include "../core/Math/Vector2.h"
#include "../core/Physics/Body.h"

namespace engine {

class Renderer {
public:
    Renderer(int width = 1024, int height = 768, const char* title = "2D Physics Engine");
    ~Renderer();

    bool isOpen() const { return window && window->isOpen(); }
    void clear();
    void display();
    void handleEvents();

    // Draw primitives
    void drawCircle(const Vector2& center, double radius, const sf::Color& color = sf::Color::White);
    void drawRect(const Vector2& pos, double width, double height, const sf::Color& color = sf::Color::White);
    void drawLine(const Vector2& from, const Vector2& to, const sf::Color& color = sf::Color::White);
    void drawText(const std::string& text, float x, float y, const sf::Color& color = sf::Color::White);

    // Draw physics objects
    void drawPointMass(const PointMass& p, double radius = 5.0, const sf::Color& color = sf::Color::Green);
    void drawVelocityVector(const PointMass& p, double scale = 1.0, const sf::Color& color = sf::Color::Red);

private:
    std::unique_ptr<sf::RenderWindow> window;
    sf::Font font;
    int windowWidth;
    int windowHeight;

    bool loadFont();
};

} // namespace engine

#else
// Stub implementation when SFML is disabled
namespace engine {
class Renderer {
public:
    Renderer(int w = 1024, int h = 768, const char* t = "") : windowWidth(w), windowHeight(h) {}
    ~Renderer() {}
    bool isOpen() const { return false; }
    void clear() {}
    void display() {}
    void handleEvents() {}
    void drawCircle(const engine::Vector2&, double, ...) {}
    void drawRect(const engine::Vector2&, double, double, ...) {}
    void drawLine(const engine::Vector2&, const engine::Vector2&, ...) {}
    void drawText(const std::string&, float, float, ...) {}
    void drawPointMass(const engine::PointMass&, ...) {}
    void drawVelocityVector(const engine::PointMass&, ...) {}
private:
    int windowWidth;
    int windowHeight;
};
} // namespace engine

#endif
