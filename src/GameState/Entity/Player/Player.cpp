//
// Created by x3r1x on 10/20/26.
//

#include "Player.hpp"

#include <cmath>

#include "../../gameConstants.hpp"

Player::Player()
{
    m_position = PLAYER_START_POSITION;
    m_stamina = PLAYER_MAX_STAMINA;

    m_view.SetPosition(m_position);
}

PlayerView &Player::GetView()
{
    return m_view;
}

float Player::GetStamina() const
{
    return m_stamina;
}

sf::Vector2f Player::GetPosition() const
{
    return m_position;
}

sf::Vector2f Player::GetVelocity() const
{
    return m_velocity;
}

void Player::SetPosition(const sf::Vector2f position)
{
    m_position = position;
    m_view.SetPosition(position);
}

void Player::SetVelocity(const sf::Vector2f velocity)
{
    m_velocity = velocity;
}

bool Player::IsGrounded() const
{
    return m_isGrounded;
}

void Player::SetGround(const bool grounded)
{
    m_isGrounded = grounded;
}

void Player::Land(const float landedY)
{
    m_position.y = landedY - m_view.GetBounds().size.y / 2;
    m_velocity.y = 0;
    m_isGrounded = true;
    m_view.SetPosition(m_position);
}

void Player::Update(const float directionX, const bool shouldSprint, const bool shouldJump,
                    const float elapsedTime)
{
    const bool isMoving = directionX != 0;

    ProcessStamina(shouldSprint, isMoving, elapsedTime);
    ProcessHorizontalVelocity(isMoving, directionX, elapsedTime);
    NormalizeHorizontalSpeed(shouldSprint);

    if (shouldJump && m_isGrounded)
    {
        m_velocity.y = -PLAYER_JUMP_SPEED;
        m_isGrounded = false;
    }

    if (!m_isGrounded)
    {
        m_velocity.y += PLAYER_GRAVITY * elapsedTime;

        if (m_velocity.y > PLAYER_MAX_FALL_SPEED)
        {
            m_velocity.y = PLAYER_MAX_FALL_SPEED;
        }
    }

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

void Player::ProcessHorizontalVelocity(const bool isMoving, const float directionX,
                                       const float elapsedTime)
{
    if (isMoving)
    {
        m_velocity.x += directionX * PLAYER_ACCELERATION * elapsedTime;
    }
    else if (const float currentSpeed = std::abs(m_velocity.x); currentSpeed > 0)
    {
        const float newSpeed = std::max(0.0f, currentSpeed - PLAYER_FRICTION * elapsedTime);
        m_velocity.x = (m_velocity.x < 0.0f ? -newSpeed : newSpeed);
    }
}

void Player::NormalizeHorizontalSpeed(const bool shouldSprint)
{
    m_isSprinting = shouldSprint && m_stamina > 0;

    const float maxSpeed =
        m_isSprinting ? PLAYER_MAX_SPEED * PLAYER_STAMINA_SPEED_MULTIPLIER : PLAYER_MAX_SPEED;

    if (std::abs(m_velocity.x) > maxSpeed)
    {
        m_velocity.x = m_velocity.x < 0 ? -maxSpeed : maxSpeed;
    }
}