//
// Created by x3r1x on 10/20/26.
//

#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

constexpr auto PLAYER_START_POSITION = sf::Vector2f(250.0, 150.0);
constexpr float PLAYER_ACCELERATION = 600.0;
constexpr float PLAYER_FRICTION = 400.0;
constexpr float PLAYER_MAX_SPEED = 200.0;
constexpr float PLAYER_GRAVITY = 800.0;
constexpr float PLAYER_JUMP_SPEED = 600.0;
constexpr float PLAYER_MAX_FALL_SPEED = 900.0;
constexpr float PLAYER_MAX_STAMINA = 100.0;
constexpr float PLAYER_STAMINA_DRAIN = 25.0;
constexpr float PLAYER_STAMINA_REGENERATION = 15.0;
constexpr float PLAYER_STAMINA_SPEED_MULTIPLIER = 1.7;
constexpr float PLAYER_SPRITE_SCALE = 0.06;

constexpr float HUD_WIDTH = 200.0;
constexpr float HUD_HEIGHT = 20.0;
constexpr auto HUD_STAMINA_SIZE = sf::Vector2f(HUD_WIDTH, HUD_HEIGHT);
constexpr auto HUD_STAMINA_BACKGROUND_COLOR = sf::Color(60, 60, 60);
constexpr auto HUD_STAMINA_FILL = sf::Color(50, 200, 80);

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

constexpr int TILE_SIZE = 50;
constexpr int MAIN_ROOM_WIDTH = 20;
constexpr int MAIN_ROOM_HEIGHT = 26;

constexpr int ENNARD_ROOM_WIDTH = 12;
constexpr int ENNARD_ROOM_HEIGHT = 10;

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
constexpr auto NOTE_TEXT = "ЗАПИСКА\nПривет!\nYou won't die, \nand It will only hurt for a moment.\n";
constexpr auto NOTE_TEXT_SIZE = 14;
constexpr auto NOTE_TEXT_FILL_COLOR = sf::Color(40, 35, 25);
constexpr auto NOTE_TEXT_OFFSET_X = 30;
constexpr auto NOTE_TEXT_OFFSET_Y = 15;