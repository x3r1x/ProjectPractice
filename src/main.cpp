//
// Created by x3r1x on 9/23/26.
//

#include <iostream>
#include <optional>

#include <SFML/Graphics.hpp>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;
constexpr int INITIAL_PLAYER_SPEED = 300;
constexpr auto DEFAULT_PLAYER_POSITION = sf::Vector2f(100, 400);

constexpr auto DEFAULT_ENEMY_VELOCITY = sf::Vector2f(200, 150);
constexpr auto INITIAL_ENEMY_POSITION = sf::Vector2f(400, 300);
constexpr auto ENEMY_SIZE = sf::Vector2f(100, 25);

constexpr sf::Color PLAYER_FILL_COLOR = sf::Color::Magenta;
constexpr sf::Color ENEMY_FILL_COLOR = sf::Color::Red;
constexpr sf::Color OUTLINE_COLOR = sf::Color::White;
constexpr sf::Color DEFAULT_BACKGROUND_COLOR = sf::Color::Green;
constexpr sf::Color CHANGED_COLOR = sf::Color::Cyan;
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

typedef struct
{
    sf::RectangleShape rectangle;

    sf::Vector2f position;
    sf::Vector2f velocity;
} Enemy;

static sf::Vector2f GetRectanglePosition(const sf::Vector2f playerPosition)
{
    return {playerPosition.x - RECTANGLE_SIZE.x / 2, playerPosition.y - RECTANGLE_SIZE.y / 2};
}

static sf::Vector2f GetLeftCirclePosition(const sf::Vector2f playerPosition)
{
    return {playerPosition.x - CIRCLE_RADIUS * 2, playerPosition.y + CIRCLE_RADIUS / 2};
}

static sf::Vector2f GetRightCirclePosition(const sf::Vector2f playerPosition)
{
    return {playerPosition.x, playerPosition.y + CIRCLE_RADIUS / 2};
}

static bool IsWindowPlayerCollision(const sf::Vector2f currentPosition, const sf::Vector2f move, const sf::Vector2f spriteOffset, const float extraBottomOffset)
{
    if (currentPosition.x + move.x + spriteOffset.x >= WINDOW_WIDTH || currentPosition.x + move.x - spriteOffset.x <= 0)
    {
        return true;
    }

    if (currentPosition.y + move.y + spriteOffset.y + extraBottomOffset >= WINDOW_HEIGHT || currentPosition.y + move.y - spriteOffset.y <= 0)
    {
        return true;
    }

    return false;
}

static bool IsWindowEnemyCollision(const sf::Vector2f currentPosition, const sf::Vector2f move, const sf::Vector2f spriteOffset)
{
    if (currentPosition.x + move.x + spriteOffset.x >= WINDOW_WIDTH || currentPosition.x + move.x <= 0)
    {
        return true;
    }

    if (currentPosition.y + move.y + spriteOffset.y >= WINDOW_HEIGHT || currentPosition.y + move.y <= 0)
    {
        return true;
    }

    return false;
}

static void InitShape(sf::Shape& shape, sf::Color color)
{
    shape.setFillColor(color);
    shape.setOutlineThickness(OUTLINE_THICKNESS);
    shape.setOutlineColor(OUTLINE_COLOR);
}

static void InitPlayer(Player& player)
{
    player.position = DEFAULT_PLAYER_POSITION;
    player.speed = INITIAL_PLAYER_SPEED;

    player.rectangle.setSize(RECTANGLE_SIZE);
    InitShape(player.rectangle, PLAYER_FILL_COLOR);

    player.leftCircle.setRadius(CIRCLE_RADIUS);
    InitShape(player.leftCircle, PLAYER_FILL_COLOR);

    player.rightCircle.setRadius(CIRCLE_RADIUS);
    InitShape(player.rightCircle, PLAYER_FILL_COLOR);
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

    const auto offset  = sf::Vector2f(direction.x * elapsedTime * player.speed,
        direction.y * elapsedTime * player.speed);

    if (!IsWindowPlayerCollision(player.position, offset, {RECTANGLE_SIZE.x / 2, RECTANGLE_SIZE.y / 2}, CIRCLE_RADIUS * 2))
    {
        player.position.x += offset.x;
        player.position.y += offset.y;
    }
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

static void InitEnemy(Enemy& enemy)
{
    enemy.position = INITIAL_ENEMY_POSITION;
    enemy.velocity = DEFAULT_ENEMY_VELOCITY;
    enemy.rectangle.setSize(ENEMY_SIZE);

    InitShape(enemy.rectangle, ENEMY_FILL_COLOR);
}

static void UpdateEnemy(Enemy& enemy, const float elapsedTime)
{
    const auto offset = sf::Vector2f(enemy.velocity.x * elapsedTime, enemy.velocity.y * elapsedTime);

    if (IsWindowEnemyCollision(enemy.position, offset, ENEMY_SIZE))
    {
        enemy.velocity.x *= -1;
        enemy.velocity.y *= -1;
    }

    enemy.position.x += offset.x;
    enemy.position.y += offset.y;
}

static void DrawEnemy(sf::RenderWindow& window, Enemy& enemy)
{
    enemy.rectangle.setPosition(enemy.position);

    window.draw(enemy.rectangle);
}

static void HandlePlayerEnemyCollision(Player& player, const Enemy& enemy)
{
    const auto enemyBounds = enemy.rectangle.getGlobalBounds();
    const auto isRectangleIntersection = player.rectangle.getGlobalBounds().findIntersection(enemyBounds);
    const auto isLeftCircleIntersection = player.leftCircle.getGlobalBounds().findIntersection(enemyBounds);
    const auto isRightCircleIntersection = player.rightCircle.getGlobalBounds().findIntersection(enemyBounds);

    if (isRectangleIntersection || isLeftCircleIntersection || isRightCircleIntersection)
    {
        player.position = DEFAULT_PLAYER_POSITION;
        std::cout << "COLLISION DETECTED!" << std::endl;
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Рыжов");
    sf::Color backgroundColor = DEFAULT_BACKGROUND_COLOR;
    sf::Clock clock;

    Player player;
    Enemy enemy;
    InitPlayer(player);
    InitEnemy(enemy);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
                window.close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
            {
                backgroundColor = CHANGED_COLOR;
            }
        }

        window.clear(backgroundColor);

        const float elapsedTime = clock.restart().asSeconds();
        UpdatePlayer(player, elapsedTime);
        UpdateEnemy(enemy, elapsedTime);

        HandlePlayerEnemyCollision(player, enemy);

        DrawPlayer(window, player);
        DrawEnemy(window, enemy);

        window.display();
    }

    return 0;
}