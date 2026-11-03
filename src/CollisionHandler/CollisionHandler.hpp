//
// Created by x3r1x on 10/21/26.
//

#ifndef SFML_TEST_COLLISIONHANDLER_H
#define SFML_TEST_COLLISIONHANDLER_H
#pragma once
#include "../Entity/Map/Map.hpp"
#include "../Entity/Player/Player.hpp"
#include "../ViewModule/View/View.hpp"

class CollisionHandler
{
    Player& m_player;
    Map& m_map;
    View& m_view;

    bool m_isInteracting = false;
    sf::FloatRect m_interactingTile;

    void HandlePlayerMapBumpByX(const std::vector<sf::FloatRect>& collidableTiles) const;
    void HandlePlayerMapBumpByY(const std::vector<sf::FloatRect>& collidableTiles) const;
    void HandlePlayerMapBump() const;
    void HandlePlayerMapInteraction();
public:
    CollisionHandler(Player &player, Map &map, View& view);

    void HandlePlayerMapCollision();
    void Interact(bool& isNoteOpen, std::string& noteText) const;
};

#endif // SFML_TEST_COLLISIONHANDLER_H
