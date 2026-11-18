//
// Created by x3r1x on 11/17/26.
//

#include "Enemy.hpp"

#include <utility>

#include "../../../GameConstants.hpp"
#include "../EnemyConstants.hpp"

Enemy::Enemy(const sf::Vector2f spawnPosition, const sf::IntRect zoneTiles,
             const std::string &spritePath, const std::string &soundPath,
             std::function<void()> onJumpScareEnd, const std::string &jumpScarePath,
             const sf::Vector2u windowSize, const float moveSpeed, const bool useGravity)
    : m_position(spawnPosition), m_zone(zoneTiles), m_moveSpeed(moveSpeed),
      m_useGravity(useGravity), m_view(spritePath, ENEMY_SPRITE_SCALE),
      m_jumpScare(jumpScarePath, soundPath, windowSize, std::move(onJumpScareEnd))
{
    m_view.SetPosition(m_position);
    ClampToZone();
}

sf::FloatRect Enemy::GetZoneWorldBounds() const
{
    return {
        {static_cast<float>(m_zone.position.x * TILE_SIZE),
         static_cast<float>(m_zone.position.y * TILE_SIZE)},
        {static_cast<float>(m_zone.size.x * TILE_SIZE),
         static_cast<float>(m_zone.size.y * TILE_SIZE)}
    };
}

bool Enemy::IsPlayerInZone(const sf::Vector2f playerPosition) const
{
    return GetZoneWorldBounds().contains(playerPosition);
}

void Enemy::ClampToZone()
{
    const sf::FloatRect zoneBounds = GetZoneWorldBounds();
    const sf::FloatRect enemyBounds = GetBounds();

    const float halfWidth = enemyBounds.size.x / 2;
    const float halfHeight = enemyBounds.size.y / 2;

    const float minX = zoneBounds.position.x + halfWidth;
    const float maxX = zoneBounds.position.x + zoneBounds.size.x - halfWidth;
    const float minY = zoneBounds.position.y + halfHeight;
    const float maxY = zoneBounds.position.y + zoneBounds.size.y - halfHeight;

    if (minX <= maxX)
    {
        if (m_position.x < minX)
        {
            m_position.x = minX;
            m_velocity.x = 0;
            CollideWithWall(false);
        }
        else if (m_position.x > maxX)
        {
            m_position.x = maxX;
            m_velocity.x = 0;
            CollideWithWall(true);
        }
    }

    if (minY <= maxY)
    {
        if (m_position.y < minY)
        {
            m_position.y = minY;
            if (m_velocity.y < 0)
            {
                m_velocity.y = 0;
            }
        }
        else if (m_position.y > maxY)
        {
            m_position.y = maxY;
            if (m_velocity.y > 0)
            {
                m_velocity.y = 0;
                m_isGrounded = true;
            }
        }
    }

    m_view.SetFacingRight(m_facingRight);
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