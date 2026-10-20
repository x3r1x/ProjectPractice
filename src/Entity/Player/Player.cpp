//
// Created by x3r1x on 10/20/26.
//

#include "Player.h"

#include <cmath>

#include "../../constants.cpp"

Player::Player()
{
    m_position = PLAYER_START_POSITION;
    m_stamina = PLAYER_MAX_STAMINA;
}

PlayerView &Player::GetView()
{
    return m_view;
}

float Player::GetStamina() const
{
    return m_stamina;
}

void Player::Update(const sf::Vector2f direction, const bool shouldSprint, const float elapsedTime)
{
    const bool isMoving = direction.x != 0 || direction.y != 0;

    ProcessStamina(shouldSprint, isMoving, elapsedTime);
    ProcessVelocityChange(isMoving, direction, elapsedTime);
    NormalizeSpeed(shouldSprint, isMoving);

    m_position.x += m_velocity.x * elapsedTime;
    m_position.y += m_velocity.y * elapsedTime;

    m_view.SetPosition(m_position);
}

void Player::ProcessStamina(const bool shouldSprint, const bool isMoving, const float elapsedTime)
{
    if (shouldSprint && isMoving && m_stamina > 0)
    {
        const float expectedStamina = m_stamina - PLAYER_STAMINA_DRAIN * elapsedTime;
        m_stamina = expectedStamina >= 0 ? expectedStamina : 0;
    }
    else if (m_stamina < PLAYER_MAX_STAMINA)
    {
        const float expectedStamina = m_stamina + PLAYER_STAMINA_REGENERATION * elapsedTime;
        m_stamina = expectedStamina >= PLAYER_MAX_STAMINA ? PLAYER_MAX_STAMINA : expectedStamina;
    }
}

void Player::ProcessVelocityChange(const bool isMoving, const sf::Vector2f direction,
                                   const float elapsedTime)
{
    if (isMoving)
    {
        m_velocity.x += direction.x * PLAYER_ACCELERATION * elapsedTime;
        m_velocity.y += direction.y * PLAYER_ACCELERATION * elapsedTime;
    }
    else
    {
        const float currentSpeed =
            std::sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);

        if (currentSpeed > 0)
        {
            const float estimatedNewSpeed = currentSpeed - PLAYER_FRICTION * elapsedTime;
            const float newSpeed = estimatedNewSpeed >= 0 ? estimatedNewSpeed : 0;

            m_velocity.x *= newSpeed / currentSpeed;
            m_velocity.y *= newSpeed / currentSpeed;
        }
    }
}

void Player::NormalizeSpeed(const bool shouldSprint, const bool isMoving)
{
    m_isSprinting = shouldSprint && isMoving && m_stamina > 0;

    const float maxSpeed = m_isSprinting ? PLAYER_MAX_SPEED * PLAYER_STAMINA_SPEED_MULTIPLIER : PLAYER_MAX_SPEED;
    const float speed = std::sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);

    if (speed > maxSpeed)
    {
        m_velocity.x = m_velocity.x / speed * maxSpeed;
        m_velocity.y = m_velocity.y / speed * maxSpeed;
    }
}