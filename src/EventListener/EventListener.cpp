//
// Created by x3r1x on 10/21/26.
//

#include "EventListener.h"

#include <cmath>

#include "../Entity/Player/Player.h"

void EventListener::HandleEvents(sf::RenderWindow &window)
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->code == sf::Keyboard::Key::Escape)
            {
                window.close();
            }
        }
    }
}

void EventListener::HandleInput(Player &player, float elapsedTime)
{
    sf::Vector2f playerDirection{0.0, 0.0};

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        playerDirection.y -= 1.0;
    }


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        playerDirection.y += 1.0;
    }


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        playerDirection.x -= 1.0;
    }


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        playerDirection.x += 1.0;
    }

    if (const float vectorLength = std::sqrt(playerDirection.x * playerDirection.x +
                                             playerDirection.y * playerDirection.y);
        vectorLength != 0)
    {
        playerDirection.x = playerDirection.x / vectorLength;
        playerDirection.y = playerDirection.y / vectorLength;
    }

    player.Update(playerDirection, elapsedTime);
}