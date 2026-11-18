//
// Created by x3r1x on 11/18/26.
//

#include "Enemies.hpp"

#include <cmath>
#include <utility>

#include "../../../GameConstants.hpp"
#include "../EnemyConstants.hpp"

FuntimeFreddy::FuntimeFreddy(const sf::Vector2f spawnPosition, const sf::IntRect zoneTiles,
                             std::function<void()> onJumpScareEnd, const sf::Vector2u windowSize)
    : Enemy(spawnPosition, zoneTiles, "../assets/png/Funtime Freddy.png", "../assets/sounds/Funtime Freddy Jumpscare Sound.mp3",
            std::move(onJumpScareEnd), "../assets/png/FuntimeFreddyJumpScare.png", windowSize,
            FUNTIME_FREDDY_MOVE_SPEED, true)
{
}

void FuntimeFreddy::UpdateBehavior(const EnemyContext &context, float)
{
    const float dx = context.playerPosition.x - m_position.x;
    const float dy = std::abs(context.playerPosition.y - m_position.y);

    if (IsPlayerInZone(context.playerPosition) && dy < 70)
    {
        const float direction = dx >= 0 ? 1 : -1;
        m_velocity.x = direction * (m_moveSpeed * 1);
    }
    else
    {
        m_velocity.x = (m_facingRight ? 1.0f : -1.0f) * m_moveSpeed;
    }
}

BonBon::BonBon(const sf::Vector2f spawnPosition, const sf::IntRect zoneTiles,
               std::function<void()> onJumpScareEnd, const sf::Vector2u windowSize)
    : Enemy(spawnPosition, zoneTiles, "../assets/png/Bon Bon.png", "../assets/sounds/Balora Jumpscare Sound.mp3",
            std::move(onJumpScareEnd), "../assets/png/BonBonJumpScare.png", windowSize, FUNTIME_FREDDY_MOVE_SPEED,
            true)
{
}

void BonBon::UpdateBehavior(const EnemyContext &context, const float deltaTime)
{
    if (IsPlayerInZone(context.playerPosition))
    {
        const float direction = context.playerPosition.x >= m_position.x ? 1 : -1;
        m_velocity.x = direction * m_moveSpeed;

        m_jumpTimer -= deltaTime;
        if (m_jumpTimer <= 0 && m_isGrounded)
        {
            m_velocity.y = -420;
            m_isGrounded = false;
            m_jumpTimer = 1.6;
        }
    }
    else
    {
        m_velocity.x = (m_facingRight ? 1.0f : -1.0f) * (m_moveSpeed * 0.8f);
    }
}

Balora::Balora(const sf::Vector2f spawnPosition, const sf::IntRect zoneTiles,
               std::function<void()> onJumpScareEnd, const sf::Vector2u windowSize)
    : Enemy(spawnPosition, zoneTiles, "../assets/png/Balora.png",  "../assets/sounds/Balora Jumpscare Sound.mp3",
            std::move(onJumpScareEnd), "../assets/png/BaloraJumpScare.png", windowSize, FUNTIME_FREDDY_MOVE_SPEED,
            true)
{
}

void Balora::UpdateBehavior(const EnemyContext &context, float)
{
    const bool playerSprinting = std::abs(context.playerVelocity.x) > PLAYER_MAX_SPEED + 10;

    if (IsPlayerInZone(context.playerPosition) && playerSprinting)
    {
        const float direction = (context.playerPosition.x >= m_position.x) ? 1 : -1;
        m_velocity.x = direction * (m_moveSpeed * 2.2f);
    }
    else
    {
        m_velocity.x = (m_facingRight ? 1.0f : -1.0f) * m_moveSpeed;
    }
}

ElecroBab::ElecroBab(const sf::Vector2f spawnPosition, const sf::IntRect zoneTiles,
                     std::function<void()> onJumpScareEnd, const sf::Vector2u windowSize)
    : Enemy(spawnPosition, zoneTiles, "../assets/png/Electrobab.png", "../assets/sounds/Bidybab Jumpscare Sound.mp3",
            std::move(onJumpScareEnd), "../assets/png/ElectroBabJumpScare.png", windowSize, FUNTIME_FREDDY_MOVE_SPEED,
            false),
      m_baseY(spawnPosition.y)
{
}

void ElecroBab::UpdateBehavior(const EnemyContext &context, const float deltaTime)
{
    m_phase += deltaTime * 4;

    if (IsPlayerInZone(context.playerPosition))
    {
        const float direction = context.playerPosition.x >= m_position.x ? 1 : -1;
        m_velocity.x = direction * (m_moveSpeed * 1.3f);
    }
    else
    {
        m_velocity.x = (m_facingRight ? 1.0f : -1.0f) * m_moveSpeed;
    }

    const float targetY = m_baseY + std::sin(m_phase) * 35;
    m_velocity.y = (targetY - m_position.y) * 5;
}

BidyBab::BidyBab(const sf::Vector2f spawnPosition, const sf::IntRect zoneTiles,
                 std::function<void()> onJumpScareEnd, const sf::Vector2u windowSize)
    : Enemy(spawnPosition, zoneTiles, "../assets/png/Bidybab.png", "../assets/sounds/Bidybab Jumpscare Sound.mp3",
            std::move(onJumpScareEnd), "../assets/png/BidyBabJumpScare.png", windowSize, FUNTIME_FREDDY_MOVE_SPEED,
            true)
{
}

void BidyBab::UpdateBehavior(const EnemyContext &context, float)
{
    if (!IsPlayerInZone(context.playerPosition))
    {
        m_velocity.x = (m_facingRight ? 1.0f : -1.0f) * (m_moveSpeed * 0.6f);
        return;
    }

    const float dx = context.playerPosition.x - m_position.x;
    const bool playerMovingTowardsMe =
        (dx > 0 && context.playerVelocity.x < -10) ||
        (dx < 0 && context.playerVelocity.x > 10);

    if (playerMovingTowardsMe)
    {
        m_velocity.x = 0;
    }
    else
    {
        const float direction = dx >= 0 ? 1 : -1;
        m_velocity.x = direction * m_moveSpeed;
    }
}

FuntimeFoxy::FuntimeFoxy(const sf::Vector2f spawnPosition, const sf::IntRect zoneTiles,
                         std::function<void()> onJumpScareEnd, const sf::Vector2u windowSize)
    : Enemy(spawnPosition, zoneTiles, "../assets/png/Funtime Foxy.png", "../assets/sounds/Funtime Foxy Jumpscare Sound.mp3",
            std::move(onJumpScareEnd), "../assets/png/FuntimeFoxyJumpScare.png", windowSize,
            FUNTIME_FREDDY_MOVE_SPEED, true)
{
}

void FuntimeFoxy::UpdateBehavior(const EnemyContext &context, const float deltaTime)
{
    if (!IsPlayerInZone(context.playerPosition))
    {
        m_isDashing = false;
        m_stateTimer = 1.5;
        m_velocity.x = (m_facingRight ? 1.0f : -1.0f) * 100.0f;
        return;
    }

    m_stateTimer -= deltaTime;

    if (!m_isDashing)
    {
        m_velocity.x = 0;
        m_facingRight = (context.playerPosition.x >= m_position.x);

        if (m_stateTimer <= 0)
        {
            m_isDashing = true;
            m_dashDirection = m_facingRight ? 1 : -1;
            m_stateTimer = 0.75;
        }
    }
    else
    {
        m_velocity.x = m_dashDirection * m_moveSpeed;
        if (m_stateTimer <= 0)
        {
            m_isDashing = false;
            m_stateTimer = 2;
        }
    }
}

//TODO: add jumpscare
CircusBaby::CircusBaby(const sf::Vector2f spawnPosition, const sf::IntRect zoneTiles,
                       std::function<void()> onJumpScareEnd, const sf::Vector2u windowSize)
    : Enemy(spawnPosition, zoneTiles, "../assets/png/Circus Baby.png", "../assets/sounds/Circus Baby Jumpscare Sound.mp3",
            std::move(onJumpScareEnd), "../assets/png/FuntimeFreddyJumpScare.png", windowSize,
            FUNTIME_FREDDY_MOVE_SPEED, true)
{
}

void CircusBaby::UpdateBehavior(const EnemyContext &context, const float deltaTime)
{
    if (!IsPlayerInZone(context.playerPosition))
    {
        m_velocity.x = (m_facingRight ? 1.0f : -1.0f) * m_moveSpeed;
        return;
    }

    const float dx = context.playerPosition.x - m_position.x;
    const float direction = dx >= 0 ? 1 : -1;
    m_velocity.x = direction * (m_moveSpeed * 1.4f);

    m_lungeTimer -= deltaTime;
    if (m_lungeTimer <= 0 && m_isGrounded)
    {
        m_velocity.y = -500;
        m_velocity.x = direction * (m_moveSpeed * 2.1f);
        m_isGrounded = false;
        m_lungeTimer = 2.4;
    }
}