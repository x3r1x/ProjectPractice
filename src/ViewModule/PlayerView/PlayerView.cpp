//
// Created by x3r1x on 10/20/26.
//

#include "PlayerView.hpp"

#include <iostream>

#include "../../constants.hpp"

constexpr auto PATH_TO_SPRITE = "../assets/Nightguard.png";

PlayerView::PlayerView(): m_sprite(m_texture)
{
    if (!m_texture.loadFromFile(PATH_TO_SPRITE))
    {
        std::cerr << "Could not load Nightguard.png" << std::endl;
        return;
    }

    m_sprite.setTextureRect(
        sf::IntRect({0, 0}, sf::Vector2i(m_texture.getSize()))
    );

    m_sprite.setScale({PLAYER_SPRITE_SCALE, PLAYER_SPRITE_SCALE});

    const auto bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin({bounds.size.x / 2, bounds.size.y / 2});
}

void PlayerView::SetPosition(const sf::Vector2f newPosition)
{
    m_sprite.setPosition(newPosition);
}

void PlayerView::Draw(sf::RenderWindow &window)
{
    window.draw(m_sprite);
}