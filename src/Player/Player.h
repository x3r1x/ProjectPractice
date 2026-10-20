//
// Created by x3r1x on 10/20/26.
//

#ifndef SFML_TEST_PLAYER_H
#define SFML_TEST_PLAYER_H
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include "../ViewModule/PlayerView/PlayerView.h"

class Player
{
    sf::Vector2f m_position;
    sf::Vector2f m_speed;

    sf::RectangleShape m_shape;

    PlayerView m_view;
public:
    Player();

    PlayerView& GetView();

    void Update(float elapsedTime);
};

#endif // SFML_TEST_PLAYER_H
