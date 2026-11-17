//
// Created by x3r1x on 11/17/26.
//

#include "Enemy.hpp"

#include <utility>

#include "../../../GameConstants.hpp"

Enemy::Enemy(const sf::Vector2f spawnPosition, const std::string &spritePath,
             const sf::Vector2f spriteScale, std::function<void()> onJumpScareEnd,
             const std::string &jumpScarePath, const sf::Vector2u windowSize, const float moveSpeed,
             const bool useGravity)
    : m_position(spawnPosition), m_moveSpeed(moveSpeed), m_useGravity(useGravity),
      m_view(spritePath, spriteScale), m_jumpScare(jumpScarePath, windowSize, std::move(onJumpScareEnd))
{
    m_view.SetPosition(m_position);
}

void Enemy::Update(const EnemyContext &context, const float deltaTime)
{
    UpdateBehavior(context, deltaTime);

    if (m_useGravity && !m_isGrounded)
    {
        m_velocity.y += PLAYER_GRAVITY * deltaTime;
        if (m_velocity.y > PLAYER_MAX_FALL_SPEED)
        {
            m_velocity.y = PLAYER_MAX_FALL_SPEED;
        }
    }

    m_position += m_velocity * deltaTime;

    if (m_velocity.x > ENEMY_VELOCITY_EPSILON)
    {
        m_facingRight = true;
    }
    else if (m_velocity.x < -ENEMY_VELOCITY_EPSILON)
    {
        m_facingRight = false;
    }

    m_view.SetFacingRight(m_facingRight);
    m_view.SetPosition(m_position);
}

void Enemy::CollideWithWall(const bool hitRightWall)
{
    m_facingRight = !hitRightWall;
}

EnemyView &Enemy::GetView()
{
    return m_view;
}

JumpScare &Enemy::GetJumpScare()
{
    return m_jumpScare;
}

sf::FloatRect Enemy::GetBounds() const
{
    return m_view.GetBounds();
}

sf::Vector2f Enemy::GetPosition() const
{
    return m_position;
}

void Enemy::SetPosition(const sf::Vector2f position)
{
    m_position = position;
    m_view.SetPosition(position);
}

sf::Vector2f Enemy::GetVelocity() const
{
    return m_velocity;
}

void Enemy::SetVelocity(const sf::Vector2f velocity)
{
    m_velocity = velocity;
}

bool Enemy::IsGrounded() const
{
    return m_isGrounded;
}

void Enemy::SetGround(const bool grounded)
{
    m_isGrounded = grounded;
}