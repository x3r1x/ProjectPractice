//
// Created by x3r1x on 11/18/26.
//

#ifndef SFML_TEST_ENEMIES_HPP
#define SFML_TEST_ENEMIES_HPP
#pragma once

#include "../Enemy/Enemy.hpp"

class FuntimeFreddy : public Enemy
{
protected:
    void UpdateBehavior(const EnemyContext &context, float deltaTime) override;

public:
    FuntimeFreddy(sf::Vector2f spawnPosition, sf::IntRect zoneTiles,
                  std::function<void()> onJumpScareEnd, sf::Vector2u windowSize);
};

class BonBon : public Enemy
{
    float m_jumpTimer = 1.5f;

protected:
    void UpdateBehavior(const EnemyContext &context, float deltaTime) override;

public:
    BonBon(sf::Vector2f spawnPosition, sf::IntRect zoneTiles,
           std::function<void()> onJumpScareEnd, sf::Vector2u windowSize);
};

class Balora : public Enemy
{
protected:
    void UpdateBehavior(const EnemyContext &context, float deltaTime) override;

public:
    Balora(sf::Vector2f spawnPosition, sf::IntRect zoneTiles,
           std::function<void()> onJumpScareEnd, sf::Vector2u windowSize);
};

class ElecroBab : public Enemy
{
    float m_baseY;
    float m_phase = 0.0f;

protected:
    void UpdateBehavior(const EnemyContext &context, float deltaTime) override;

public:
    ElecroBab(sf::Vector2f spawnPosition, sf::IntRect zoneTiles,
              std::function<void()> onJumpScareEnd, sf::Vector2u windowSize);
};

class BidyBab : public Enemy
{
protected:
    void UpdateBehavior(const EnemyContext &context, float deltaTime) override;

public:
    BidyBab(sf::Vector2f spawnPosition, sf::IntRect zoneTiles,
            std::function<void()> onJumpScareEnd, sf::Vector2u windowSize);
};

class FuntimeFoxy : public Enemy
{
    float m_stateTimer = 2.0f;
    float m_dashDirection = 1.0f;
    bool m_isDashing = false;

protected:
    void UpdateBehavior(const EnemyContext &context, float deltaTime) override;

public:
    FuntimeFoxy(sf::Vector2f spawnPosition, sf::IntRect zoneTiles,
                std::function<void()> onJumpScareEnd, sf::Vector2u windowSize);
};

class CircusBaby : public Enemy
{
    float m_lungeTimer = 2.5f;

protected:
    void UpdateBehavior(const EnemyContext &context, float deltaTime) override;

public:
    CircusBaby(sf::Vector2f spawnPosition, sf::IntRect zoneTiles,
               std::function<void()> onJumpScareEnd, sf::Vector2u windowSize);
};

#endif // SFML_TEST_ENEMIES_HPP
