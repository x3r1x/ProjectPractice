//
// Created by x3r1x on 11/17/26.
//

#ifndef SFML_TEST_ENEMY_HPP
#define SFML_TEST_ENEMY_HPP
#pragma once
#include <SFML/System/Vector2.hpp>

#include "../../../ViewModule/EnemyView/EnemyView.hpp"
#include "../../../ViewModule/JumpScare/JumpScare.hpp"
#include "../EnemyType.hpp"

class Enemy
{
protected:
    sf::Vector2f m_position;
    sf::Vector2f m_velocity{0.0, 0.0};
    float m_moveSpeed;
    bool m_useGravity;
    bool m_isGrounded = false;
    bool m_facingRight = true;

    EnemyView m_view;
    JumpScare m_jumpScare;

    virtual void UpdateBehavior(const EnemyContext &context, float deltaTime) = 0;

public:
    Enemy(sf::Vector2f spawnPosition, const std::string &spritePath, sf::Vector2f spriteScale,
          const std::string &jumpScarePath, sf::Vector2u windowSize, float moveSpeed,
          bool useGravity = true);
    virtual ~Enemy() = default;

    void Update(const EnemyContext &context, float deltaTime);
    virtual void CollideWithWall(bool hitRightWall);

    EnemyView &GetView();
    JumpScare &GetJumpScare();
    sf::FloatRect GetBounds() const;

    sf::Vector2f GetPosition() const;
    void SetPosition(sf::Vector2f position);

    sf::Vector2f GetVelocity() const;
    void SetVelocity(sf::Vector2f velocity);

    bool IsGrounded() const;
    void SetGround(bool grounded);
};

#endif // SFML_TEST_ENEMY_HPP
