//
// Created by x3r1x on 10/20/26.
//

#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

constexpr auto PLAYER_START_POSITION = sf::Vector2f(500.0, 1980.0);
constexpr float PLAYER_ACCELERATION = 460.0;
constexpr float PLAYER_FRICTION = 510.0;
constexpr float PLAYER_MAX_SPEED = 200.0;
constexpr float PLAYER_GRAVITY = 980.0;
constexpr float PLAYER_JUMP_SPEED = 550.0;
constexpr float PLAYER_MAX_FALL_SPEED = 1000.0;
constexpr float PLAYER_MAX_STAMINA = 100.0;
constexpr float PLAYER_STAMINA_DRAIN = 25.0;
constexpr float PLAYER_STAMINA_REGENERATION = 15.0;
constexpr float PLAYER_STAMINA_SPEED_MULTIPLIER = 1.3;
constexpr float PLAYER_SPRITE_SCALE = 0.06;

constexpr float HUD_WIDTH = 200.0;
constexpr float HUD_HEIGHT = 20.0;
constexpr auto HUD_STAMINA_SIZE = sf::Vector2f(HUD_WIDTH, HUD_HEIGHT);
constexpr auto HUD_STAMINA_BACKGROUND_COLOR = sf::Color(60, 60, 60);
constexpr auto HUD_STAMINA_FILL = sf::Color(50, 200, 80);

constexpr float GAME_CAMERA_ZOOM = 0.4;

constexpr int TILE_SIZE = 50;
constexpr int MAIN_ROOM_WIDTH = 20;
constexpr int MAIN_ROOM_HEIGHT = 41;
constexpr auto MAIN_ROOM_FROM_CIRCUS_SPAWN_POSITION = sf::Vector2f(850.0, 1980.0);
constexpr auto MAIN_ROOM_FROM_ELECTRICAL_SPAWN_POSITION = sf::Vector2f(500.0, 680.0);

constexpr int ENNARD_ROOM_WIDTH = 12;
constexpr int ENNARD_ROOM_HEIGHT = 10;
constexpr auto ENNARD_ROOM_SPAWN_POSITION = sf::Vector2f(300, 480);

constexpr int CIRCUS_BABY_ROOM_WIDTH = 20;
constexpr int CIRCUS_BABY_ROOM_HEIGHT = 16;
constexpr auto CIRCUS_BABY_SPAWN_POSITION = sf::Vector2f(500, 800);

constexpr int ELECTRICAL_ROOM_WIDTH = 12;
constexpr int ELECTRICAL_ROOM_HEIGHT = 10;
constexpr auto ELECTRICAL_SPAWN_POSITION = sf::Vector2f(100, 480);

constexpr float EPSILON = 0.001;
constexpr float INTERACTION_DISTANCE = 25;
constexpr auto INTERACTION_TEXT = "E";
constexpr auto INTERACTION_TEXT_SIZE = 22;
constexpr auto INTERACTION_TEXT_FILL_COLOR = sf::Color::White;

constexpr auto NOTE_BACKGROUND_COLOR = sf::Color(225, 210, 175);
constexpr auto NOTE_BACKGROUND_WIDTH_MULTIPLIER = 0.35;
constexpr auto NOTE_BACKGROUND_HEIGHT_MULTIPLIER = 0.8;
constexpr auto NOTE_SCREEN_WIDTH = 0.3;
constexpr auto NOTE_SCREEN_HEIGHT = 0.1;
constexpr auto NOTE_TEXT_SIZE = 14;
constexpr auto NOTE_TEXT_FILL_COLOR = sf::Color(40, 35, 25);
constexpr auto NOTE_TEXT_OFFSET_X = 30;
constexpr auto NOTE_TEXT_OFFSET_Y = 15;

constexpr auto PAUSE_BACKGROUND_TINT_COLOR = sf::Color(0, 0, 0, 150);
constexpr int PAUSE_TEXT_FONT_SIZE = 44;
constexpr auto PAUSE_TEXT_FILL_COLOR = sf::Color(150, 150, 150);
constexpr int PAUSE_TEXT_OUTLINE_THICKNESS = 8;
constexpr auto PAUSE_TEXT_OUTLINE_COLOR = sf::Color(46, 0, 180);
constexpr auto PAUSE_TEXT_HOVER_COLOR = sf::Color(226, 222, 244);

constexpr auto PAUSE_TEXT = "GAME PAUSED";
constexpr auto PAUSE_TEXT_OFFSET_RATIO = sf::Vector2f(0.5, 0.4);

constexpr auto CONTINUE_TEXT = "CONTINUE";
constexpr auto CONTINUE_TEXT_OFFSET_RATIO = sf::Vector2f(0.5, 0.5);

constexpr auto EXIT_TEXT = "EXIT";
constexpr auto EXIT_TEXT_OFFSET_RATIO = sf::Vector2f(0.5, 0.57);