//
// Created by x3r1x on 10/20/26.
//

#include "PlayerView.h"
#include "../../constants.cpp"

PlayerView::PlayerView()
{
    m_sprite = sf::RectangleShape(PLAYER_SIZE);
    m_sprite.setFillColor(sf::Color::Green);
}

void PlayerView::SetPosition(sf::Vector2f newPosition)
{
    m_sprite.setPosition(newPosition);
}

void PlayerView::Draw(sf::RenderWindow &window)
{
    window.draw(m_sprite);
}