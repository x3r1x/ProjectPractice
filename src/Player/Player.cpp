//
// Created by x3r1x on 10/20/26.
//

#include "Player.h"
#include "../constants.cpp"

Player::Player()
{
    m_position = PLAYER_POSITION;
    m_speed = sf::Vector2f(10, 10);

    m_shape = sf::RectangleShape(PLAYER_SIZE);
    m_shape.setFillColor(sf::Color::Green);
}

void Player::Update(const float elapsedTime)
{
    m_position.x += m_speed.x * elapsedTime;
    m_position.y += m_speed.y * elapsedTime;

    m_view.SetPosition(m_position);
}

PlayerView &Player::GetView()
{
    return m_view;
}