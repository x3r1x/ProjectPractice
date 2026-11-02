//
// Created by x3r1x on 10/21/26.
//

#ifndef SFML_TEST_HUD_H
#define SFML_TEST_HUD_H
#pragma once
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "../IDrawable.hpp"

class Player;
class Hud: public IDrawable
{
    const Player& m_player;
    sf::RectangleShape m_staminaBackground;
    sf::RectangleShape m_staminaFill;

    bool m_isShowingNote = false;
    sf::Font m_noteFont;
    sf::Text m_noteText{m_noteFont};
    sf::RectangleShape m_noteBackground;
public:
    explicit Hud(const Player& player);

    void SetIsShowingNote(bool isShowingNote);
    void Draw(sf::RenderWindow &window) override;
};

#endif // SFML_TEST_HUD_H
