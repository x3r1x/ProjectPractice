//
// Created by x3r1x on 10/20/26.
//

#ifndef SFML_TEST_PLAYERVIEW_H
#define SFML_TEST_PLAYERVIEW_H
#pragma once
#include "../IDrawable.hpp"
#include <SFML/Graphics.hpp>

class PlayerView: public IDrawable
{
    sf::Texture m_texture;
    sf::Sprite m_sprite;
public:
    PlayerView();

    void SetPosition(sf::Vector2f newPosition);
    void Draw(sf::RenderWindow &window) override;
};

#endif // SFML_TEST_PLAYERVIEW_H
