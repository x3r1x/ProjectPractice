//
// Created by x3r1x on 10/21/26.
//

#include "EventListener.hpp"

#include "../Entity/Player/Player.hpp"

void EventListener::HandleEvents(sf::RenderWindow &window, const CollisionHandler &collisionHandler,
                                 bool &isNoteOpen, std::string &noteText)
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }

        if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->code == sf::Keyboard::Key::Escape)
            {
                if (isNoteOpen)
                {
                    isNoteOpen = false;
                }
                else
                {
                    window.close();
                }
            }

            if (keyPressed->code == sf::Keyboard::Key::E)
            {
                if (isNoteOpen)
                {
                    isNoteOpen = false;
                }
                else
                {
                    collisionHandler.Interact(isNoteOpen, noteText);
                }
            }
        }
    }
}

void EventListener::HandleInput(Player &player, const float elapsedTime)
{
    float directionX = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        directionX -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        directionX += 1;
    }

    const bool isSprinting = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) ||
                             sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift);

    bool spacePressed = false;
    const bool isSpacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
    const bool isJumping = isSpacePressed && !spacePressed;
    spacePressed = isSpacePressed;

    player.Update(directionX, isSprinting, isJumping, elapsedTime);
}