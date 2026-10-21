//
// Created by x3r1x on 10/20/26.
//

#ifndef SFML_TEST_GAME_H
#define SFML_TEST_GAME_H
#pragma once
#include "../CollisionHandler/CollisionHandler.h"
#include "../Entity/Map/Map.h"
#include "../Entity/Player/Player.h"
#include "../EventListener/EventListener.h"
#include "../ViewModule/View/View.h"

class Game
{
    Player m_player;
    Map m_map;
    CollisionHandler m_collisionHandler;
    View m_view;
    sf::Clock m_clock;

    bool m_isRunning{};
public:
    Game();
    ~Game();

    void StartGame();
    void EndGame();
};

#endif // SFML_TEST_GAME_H
