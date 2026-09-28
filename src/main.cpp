//
// Created by x3r1x on 9/23/26.
//

#include <SFML/Graphics.hpp>
#include <optional>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

constexpr sf::Color FILL_COLOR = sf::Color::Magenta;
constexpr sf::Color OUTLINE_COLOR = sf::Color::Red;
constexpr sf::Color DEFAULT_BACKGROUND_COLOR = sf::Color::Green;
constexpr sf::Color CHANGED_BACKGROUND_COLOR = sf::Color::Cyan;
constexpr float OUTLINE_THICKNESS = 3.f;

constexpr auto RECTANGLE_SIZE = sf::Vector2f(240, 50);
constexpr auto RECTANGLE_POSITION = sf::Vector2f(400, 300);

constexpr float LEFT_CIRCLE_RADIUS = 50.f;
constexpr auto LEFT_CIRCLE_POSITION = sf::Vector2f(410, 350);

constexpr float RIGHT_CIRCLE_RADIUS = 50.f;
constexpr auto RIGHT_CIRCLE_POSITION = sf::Vector2f(530, 350);

static void DrawShape(sf::Shape& shape, const sf::Vector2f position, sf::RenderWindow& window)
{
    shape.setFillColor(FILL_COLOR);
    shape.setOutlineThickness(OUTLINE_THICKNESS);
    shape.setFillColor(OUTLINE_COLOR);
    shape.setPosition(position);

    window.draw(shape);
}

static void DrawRectangle(sf::RenderWindow& window)
{
    sf::RectangleShape rectangle(RECTANGLE_SIZE);

    DrawShape(rectangle, RECTANGLE_POSITION, window);
}

static void DrawLeftCircle(sf::RenderWindow& window)
{
    sf::CircleShape circle(LEFT_CIRCLE_RADIUS);

    DrawShape(circle, LEFT_CIRCLE_POSITION, window);
}

static void DrawRightCircle(sf::RenderWindow& window)
{
    sf::CircleShape circle(RIGHT_CIRCLE_RADIUS);

    DrawShape(circle, RIGHT_CIRCLE_POSITION, window);
}

int main() {
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Рыжов");
    sf::Color color = DEFAULT_BACKGROUND_COLOR;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
                window.close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
            {
                color = CHANGED_BACKGROUND_COLOR;
            }
        }

        window.clear(color);

        DrawRectangle(window);
        DrawLeftCircle(window);
        DrawRightCircle(window);

        window.display();
    }

    return 0;
}