//
// Created by x3r1x on 10/21/26.
//

#ifndef SFML_TEST_COLLISIONHANDLER_H
#define SFML_TEST_COLLISIONHANDLER_H
#pragma once
#include "../Entity/Map/Map.h"
#include "../Entity/Player/Player.h"

class CollisionHandler
{
    Player& m_player;
    Map& m_map;
public:
    CollisionHandler(Player& player, Map& map);

    void HandlePlayerMapCollision() const;
};

#endif // SFML_TEST_COLLISIONHANDLER_H
