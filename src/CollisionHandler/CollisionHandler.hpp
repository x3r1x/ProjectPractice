//
// Created by x3r1x on 10/21/26.
//

#ifndef SFML_TEST_COLLISIONHANDLER_H
#define SFML_TEST_COLLISIONHANDLER_H
#pragma once
#include "../Entity/Map/Map.hpp"
#include "../Entity/Player/Player.hpp"



class CollisionHandler
{
    Player& m_player;
    Map& m_map;

    static bool IntersectsX(sf::FloatRect a, sf::FloatRect b);
    static bool IntersectsY(sf::FloatRect a, sf::FloatRect b);

    void HandlePlayerMapCollisionByX() const;
    void HandlePlayerMapCollisionByY() const;
public:
    CollisionHandler(Player &player, Map &map);

    void HandlePlayerMapCollision() const;
};

#endif // SFML_TEST_COLLISIONHANDLER_H
