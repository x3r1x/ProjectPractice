//
// Created by x3r1x on 11/17/26.
//

#include "EnemyView.hpp"

#include <iostream>

EnemyView::EnemyView(const std::string &texturePath, const sf::Vector2f scale)
    : m_sprite(m_texture), m_baseScale(scale)
{
    if (!m_texture.loadFromFile(texturePath))
    {
        std::cerr << "Erroor loading enemy texture: " << texturePath << std::endl;
        return;
    }

    m_sprite.setTextureRect(sf::IntRect({0, 0}, sf::Vector2i(m_texture.getSize())));
    m_sprite.setScale(m_baseScale);

    const auto bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin({bounds.size.x / 2.0f, bounds.size.y / 2.0f});
}

sf::FloatRect EnemyView::GetBounds() const
{
    return m_sprite.getGlobalBounds();
}

void EnemyView::SetPosition(const sf::Vector2f position)
{
    m_sprite.setPosition(position);
}

void EnemyView::SetFacingRight(const bool facingRight)
{
    if (m_facingRight == facingRight)
    {
        return;
    }

    m_facingRight = facingRight;
    m_sprite.setScale({m_facingRight ? m_baseScale.x : -m_baseScale.x, m_baseScale.y});
}

void EnemyView::Draw(sf::RenderWindow &window)
{
    window.draw(m_sprite);
}