//
// Created by x3r1x on 11/17/26.
//

#ifndef SFML_TEST_ENEMYVIEW_HPP
#define SFML_TEST_ENEMYVIEW_HPP
#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "../IDrawable.hpp"

class EnemyView : public IDrawable
{
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    sf::Vector2f m_baseScale;

    bool m_facingRight = true;
public:
    EnemyView(const std::string &texturePath, sf::Vector2f scale);

    sf::FloatRect GetBounds() const;
    void SetPosition(sf::Vector2f position);
    void SetFacingRight(bool facingRight);

    void Draw(sf::RenderWindow &window) override;
};

#endif // SFML_TEST_ENEMYVIEW_HPP
