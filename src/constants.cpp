//
// Created by x3r1x on 10/20/26.
//

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

constexpr auto PLAYER_START_POSITION = sf::Vector2f(150.0, 150.0);
constexpr auto PLAYER_SIZE = sf::Vector2f(50, 50);
constexpr auto PLAYER_BOUNDS = sf::Vector2f(50, 50);
constexpr float PLAYER_ACCELERATION = 600.0;
constexpr float PLAYER_FRICTION = 400.0;
constexpr float PLAYER_MAX_SPEED = 200.0;
constexpr float PLAYER_MAX_STAMINA = 100.0;
constexpr float PLAYER_STAMINA_DRAIN = 25.0;
constexpr float PLAYER_STAMINA_REGENERATION = 15.0;
constexpr float PLAYER_STAMINA_SPEED_MULTIPLIER = 1.7;

constexpr float HUD_WIDTH = 200.0;
constexpr float HUD_HEIGHT = 20.0;
constexpr auto HUD_STAMINA_SIZE = sf::Vector2f(HUD_WIDTH, HUD_HEIGHT);
constexpr auto HUD_STAMINA_BACKGROUND_COLOR = sf::Color(60, 60, 60);
constexpr auto HUD_STAMINA_FILL = sf::Color(50, 200, 80);

constexpr auto MAP_SIZE = sf::Vector2f(1000, 1000);

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;