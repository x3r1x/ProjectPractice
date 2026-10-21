//
// Created by x3r1x on 10/20/26.
//

#ifndef SFML_TEST_PLAYER_H
#define SFML_TEST_PLAYER_H
#pragma once
#include <SFML/System/Vector2.hpp>
#include "../../ViewModule/PlayerView/PlayerView.h"

class Player
{
    sf::Vector2f m_bounds;
    sf::Vector2f m_position;
    sf::Vector2f m_velocity;
    float m_stamina;
    bool m_isSprinting = false;

    PlayerView m_view;

    void ProcessStamina(bool shouldSprint, bool isMoving, float elapsedTime);
    void ProcessVelocityChange(bool isMoving, sf::Vector2f direction, float elapsedTime);
    void NormalizeSpeed(bool shouldSprint, bool isMoving);
public:
    Player();

    PlayerView& GetView();
    float GetStamina() const;
    sf::Vector2f GetVelocity() const;
    sf::Vector2f GetPosition() const;
    sf::Vector2f GetBounds() const;

    void SetPosition(sf::Vector2f position);
    void SetVelocity(sf::Vector2f velocity);

    void Update(sf::Vector2f direction, bool shouldSprint, float elapsedTime);
};

#endif // SFML_TEST_PLAYER_H
