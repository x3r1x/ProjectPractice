//
// Created by gleb.ryzhov on 11/17/26.
//

#pragma once
#include <SFML/Graphics/Color.hpp>

constexpr auto GAME_LOST_TEXT = "EXIT";
constexpr int GAME_LOST_TEXT_FONT_SIZE = 44;
constexpr auto GAME_LOST_TEXT_FILL_COLOR = sf::Color(150, 150, 150);
constexpr int GAME_LOST_TEXT_OUTLINE_THICKNESS = 8;
constexpr auto GAME_LOST_TEXT_OUTLINE_COLOR = sf::Color(46, 0, 180);
constexpr auto GAME_LOST_TEXT_HOVER_COLOR = sf::Color(226, 222, 244);
constexpr auto GAME_LOST_TEXT_OFFSET_RATIO = sf::Vector2f(0.5, 0.8);
constexpr float GAME_LOST_DEATH_SCREEN_DURATION = 4;
constexpr float GAME_LOST_FRAME_DURATION = 0.001;
constexpr auto GAME_LOST_DEATH_FRAME_SIZE = sf::Vector2i(596, 335);