//
// Created by x3r1x on 9/23/26.
//

#include <iostream>
#include <optional>

#include <SFML/Graphics.hpp>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;
constexpr int DEFAULT_PLAYER_SPEED = 30;
constexpr auto DEFAULT_PLAYER_POSITION = sf::Vector2f(400, 300);

constexpr sf::Color FILL_COLOR = sf::Color::Magenta;
constexpr sf::Color OUTLINE_COLOR = sf::Color::Red;
constexpr sf::Color DEFAULT_BACKGROUND_COLOR = sf::Color::Green;
constexpr sf::Color CHANGED_BACKGROUND_COLOR = sf::Color::Cyan;
constexpr float OUTLINE_THICKNESS = 3;

constexpr auto RECTANGLE_SIZE = sf::Vector2f(200, 50);
constexpr float CIRCLE_RADIUS = 50;

typedef struct
{
    sf::RectangleShape rectangle;
    sf::CircleShape leftCircle;
    sf::CircleShape rightCircle;

    sf::Vector2f position;
    float speed;
} Player;

static sf::Vector2f GetRectanglePosition(const sf::Vector2f playerPosition)
{
    return sf::Vector2f(playerPosition.x - RECTANGLE_SIZE.x / 2, playerPosition.y - RECTANGLE_SIZE.y / 2);
}

static sf::Vector2f GetLeftCirclePosition(const sf::Vector2f playerPosition)
{
    return sf::Vector2f(playerPosition.x - CIRCLE_RADIUS * 2, playerPosition.y + CIRCLE_RADIUS / 2);
}

static sf::Vector2f GetRightCirclePosition(const sf::Vector2f playerPosition)
{
    return sf::Vector2f(playerPosition.x, playerPosition.y + CIRCLE_RADIUS / 2);
}

static void InitShape(sf::Shape& shape, const sf::Vector2f position)
{
    shape.setFillColor(FILL_COLOR);
    shape.setOutlineThickness(OUTLINE_THICKNESS);
    shape.setFillColor(OUTLINE_COLOR);
    shape.setPosition(position);
}

static void InitPlayer(Player& player)
{
    player.position = DEFAULT_PLAYER_POSITION;
    player.speed = DEFAULT_PLAYER_SPEED;

    player.rectangle.setSize(RECTANGLE_SIZE);
    InitShape(player.rectangle, GetRectanglePosition(player.position));

    player.leftCircle.setRadius(CIRCLE_RADIUS);
    InitShape(player.leftCircle, GetLeftCirclePosition(player.position));

    player.rightCircle.setRadius(CIRCLE_RADIUS);
    InitShape(player.rightCircle, GetRightCirclePosition(player.position));
}

static sf::Vector2f GetMovementDirection()
{
    sf::Vector2f direction(0, 0);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        direction.y -= 1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        direction.x += 1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        direction.y += 1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        direction.x -= 1;
    }

    const float directionLength = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (directionLength != 0)
    {
        direction.x = direction.x / directionLength;
        direction.y = direction.y / directionLength;
    }

    return direction;
}

static void UpdatePlayer(Player& player, const float elapsedTime)
{
    const sf::Vector2f direction = GetMovementDirection();

    player.position.x += direction.x * elapsedTime * player.speed;
    player.position.y += direction.y * elapsedTime * player.speed;
}

static void DrawPlayer(sf::RenderWindow& window, Player& player)
{
    player.rectangle.setPosition(GetRectanglePosition(player.position));
    player.leftCircle.setPosition(GetLeftCirclePosition(player.position));
    player.rightCircle.setPosition(GetRightCirclePosition(player.position));

    window.draw(player.rectangle);
    window.draw(player.leftCircle);
    window.draw(player.rightCircle);
}

//TODO: make collisions
int main() {
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Рыжов");
    sf::Color color = DEFAULT_BACKGROUND_COLOR;
    sf::Clock clock;

    Player player;
    InitPlayer(player);

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

        UpdatePlayer(player, clock.restart().asSeconds());
        DrawPlayer(window, player);

        window.display();
    }

    return 0;
}