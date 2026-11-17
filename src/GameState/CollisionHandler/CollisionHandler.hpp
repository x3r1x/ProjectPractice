//
// Created by x3r1x on 10/21/26.
//

#ifndef SFML_TEST_COLLISIONHANDLER_H
#define SFML_TEST_COLLISIONHANDLER_H
#pragma once
#include "../Entity/Enemy/Enemy/Enemy.hpp"
#include "../Entity/Map/Map.hpp"
#include "../ViewModule/View/View.hpp"

class CollisionHandler
{
    Player &m_player;
    std::vector<std::unique_ptr<Enemy>> &m_enemies;
    Map &m_map;
    View &m_view;

    IInteractable *m_currentInteractable = nullptr;

    void HandlePlayerMapBumpByX(const std::vector<sf::FloatRect> &collidableTiles) const;
    void HandlePlayerMapBumpByY(const std::vector<sf::FloatRect> &collidableTiles) const;
    void HandlePlayerMapBump() const;
    void HandlePlayerMapInteraction();

    void HandleEnemyMapCollisionByX(Enemy &enemy,
                                    const std::vector<sf::FloatRect> &collidableTiles) const;
    void HandleEnemyMapCollisionByY(Enemy &enemy,
                                    const std::vector<sf::FloatRect> &collidableTiles) const;

public:
    CollisionHandler(Player &player, std::vector<std::unique_ptr<Enemy>> &enemies, Map &map,
                     View &view);

    void HandlePlayerMapCollision();
    void HandleEnemiesMapCollision() const;
    void Interact(bool &isNoteOpen, std::string &noteText);
};

#endif // SFML_TEST_COLLISIONHANDLER_H
