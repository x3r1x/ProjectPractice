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
    static void HandleEvents(const sf::Event &event, const CollisionHandler &collisionHandler,
                             bool &isNoteOpen, std::string &noteText);
    static void HandleInput(Player &player, float elapsedTime);
};

#endif // SFML_TEST_EVENTLISTENER_H
