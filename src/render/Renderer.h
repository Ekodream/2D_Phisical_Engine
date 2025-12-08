#pragma once

#include <SFML/Graphics.hpp>
#include "../core/Math/Vector2.h"
#include "../core/Physics/Body.h"
#include <optional>
#include <vector>

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
    void drawCircleOutline(const Vector2& center, double radius, const sf::Color& color = sf::Color::White, float thickness = 2.0f);

    // Input events
    enum class InputType { None, MouseClick, MouseDrag, KeyPressed };
    struct InputEvent {
        InputType type = InputType::None;
        engine::Vector2 pos;       // for MouseClick: click pos; for MouseDrag: start
        engine::Vector2 pos2;      // for MouseDrag: release pos
        int key = -1;              // for KeyPressed: sf::Keyboard::Key
        int mouseButton = -1;      // for Mouse events: sf::Mouse::Button
    };

    // Poll the next input event
    std::optional<InputEvent> pollInput();

private:
    std::unique_ptr<sf::RenderWindow> window;
    sf::Font font;
    int windowWidth;
    int windowHeight;

    bool loadFont();

    // Input handling
    std::vector<InputEvent> inputQueue;
    engine::Vector2 mouseDownPos;
    bool mouseDown = false;
    int mouseDownButton = -1;
};

}
