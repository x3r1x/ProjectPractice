//
// Created by x3r1x on 10/21/26.
//

#ifndef SFML_TEST_EVENTLISTENER_H
#define SFML_TEST_EVENTLISTENER_H
#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "../CollisionHandler/CollisionHandler.hpp"

class Player;
class EventListener
{
public:
    static void HandleEvents(sf::RenderWindow& window, CollisionHandler& collisionHandler);
    static void HandleInput(Player& player, float elapsedTime);
};

#endif // SFML_TEST_EVENTLISTENER_H
