//
// Created by x3r1x on 11/10/26.
//

#pragma once

constexpr float BACKGROUND_ROWS = 4;
constexpr float BACKGROUND_COLUMNS = 4;

constexpr float BACKGROUND_COLUMN_INTERVAL = 10;
constexpr float BACKGROUND_ROW_INTERVAL = 0.15;
constexpr int BACKGROUND_SINGULAR_TINT = 110;
constexpr auto BACKGROUND_TINT =
    sf::Color(BACKGROUND_SINGULAR_TINT, BACKGROUND_SINGULAR_TINT, BACKGROUND_SINGULAR_TINT);

constexpr int MAIN_MENU_TEXT_FONT_SIZE = 44;
constexpr auto MAIN_MENU_TEXT_FILL_COLOR = sf::Color(150, 150, 150);
constexpr int MAIN_MENU_TEXT_OUTLINE_THICKNESS = 8;
constexpr auto MAIN_MENU_TEXT_OUTLINE_COLOR = sf::Color(46, 0, 180);
constexpr auto MAIN_MENU_TEXT_HOVER_COLOR = sf::Color(226, 222, 244);

constexpr auto MAIN_MENU_TITLE_TEXT = "NIGHT AT BABY'S\nSister Location";
constexpr auto MAIN_MENU_TITLE_OFFSET_RATIO = sf::Vector2f(0.6, 0.2);

constexpr auto MAIN_MENU_PLAY_TEXT = "PLAY";
constexpr auto MAIN_MENU_PLAY_OFFSET_RATIO = sf::Vector2f(0.6, 0.45);

constexpr auto MAIN_MENU_OPTIONS_TEXT = "OPTIONS";
constexpr auto MAIN_MENU_OPTIONS_OFFSET_RATIO = sf::Vector2f(0.6, 0.52);

constexpr auto MAIN_MENU_HTP_TEXT = "TUTORIAL";
constexpr auto MAIN_MENU_HTP_OFFSET_RATIO = sf::Vector2f(0.6, 0.59);

constexpr auto MAIN_MENU_EXIT_TEXT = "EXIT";
constexpr auto MAIN_MENU_EXIT_OFFSET_RATIO = sf::Vector2f(0.6, 0.66);

constexpr int MAIN_MENU_PLAY_TEXT_INDEX = 1;
constexpr int MAIN_MENU_EXIT_TEXT_INDEX = 4;