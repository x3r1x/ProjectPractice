//
// Created by x3r1x on 10/20/26.
//

#ifndef SFML_TEST_PLAYER_H
#define SFML_TEST_PLAYER_H
#pragma once
#include <SFML/System/Vector2.hpp>
#include "../../ViewModule/PlayerView/PlayerView.hpp"

class Player
{
    sf::Vector2f m_position;
    sf::Vector2f m_velocity;
    float m_stamina;
    bool m_isSprinting = false;
    bool m_isGrounded = false;

    PlayerView m_view;

    void ProcessStamina(bool shouldSprint, bool isMoving, float elapsedTime);
    void ProcessHorizontalVelocity(bool isMoving, float directionX, float elapsedTime);
    void NormalizeHorizontalSpeed(bool shouldSprint);
public:
    Player();

    PlayerView& GetView();
    float GetStamina() const;
    sf::Vector2f GetVelocity() const;
    sf::Vector2f GetPosition() const;
    bool IsGrounded() const;
    void SetGround(bool grounded);

    void SetPosition(sf::Vector2f position);
    void SetVelocity(sf::Vector2f velocity);

    void Land(float landedY);
    void Update(float directionX, bool shouldSprint, bool shouldJump, float elapsedTime);
};

#endif // SFML_TEST_PLAYER_H
