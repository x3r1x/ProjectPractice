//
// Created by gleb.ryzhov on 11/11/26.
//

#ifndef SFML_TEST_MENUBACKGROUND_H
#define SFML_TEST_MENUBACKGROUND_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "../MainMenuConstants.hpp"

class MenuBackground
{
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    sf::Vector2i m_frameSize;
    float m_rowTimeRemaining = BACKGROUND_ROW_INTERVAL;
    float m_columnTimeRemaining = BACKGROUND_COLUMN_INTERVAL;
    int m_row{};
    int m_column{};

    void SetSprite();
public:
    MenuBackground();

    void Update(float deltaTime);
    void Draw(sf::RenderWindow& window) const;
};

#endif // SFML_TEST_MENUBACKGROUND_H
