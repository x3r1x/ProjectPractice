//
// Created by x3r1x on 11/3/26.
//

#pragma once

#include <SFML/System/Vector2.hpp>

constexpr auto TUTORIAL_TITLE_TEXT = "TUTORIAL";
constexpr auto TUTORIAL_TITLE_OFFSET_RATIO = sf::Vector2f(0.1, 0.12);
constexpr auto TUTORIAL_BACK_OFFSET_RATIO = sf::Vector2f(0.1, 0.83);
constexpr auto TUTORIAL_BACK_TEXT = "BACK";

constexpr auto TUTORIAL_BODY_OFFSET_RATIO = sf::Vector2f(0.1, 0.27);
constexpr unsigned int TUTORIAL_BODY_FONT_SIZE = 24;
constexpr auto TUTORIAL_TEXT =
    "A & D - move left & right\n"
    "SHIFT - sprint\n"
    "SPACE - jump\n"
    "E - interact\n"
    "ESC - pause & resume\n\n";

constexpr auto TUTORiAL_TINT_COLOR = sf::Color(0, 0, 0, 170);