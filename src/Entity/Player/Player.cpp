//
// Created by x3r1x on 10/20/26.
//

#include "Player.h"
#include "../../constants.cpp"

Player::Player()
{
    m_position = PLAYER_POSITION;

    m_shape = sf::RectangleShape(PLAYER_SIZE);
    m_shape.setFillColor(sf::Color::Green);
}

void Player::Update(const sf::Vector2f direction, const float elapsedTime)
{
    m_position.x += PLAYER_SPEED * direction.x * elapsedTime;
    m_position.y += PLAYER_SPEED * direction.y * elapsedTime;

    m_view.SetPosition(m_position);
}

PlayerView &Player::GetView()
{
    return m_view;
}