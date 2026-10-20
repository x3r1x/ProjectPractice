//
// Created by x3r1x on 10/20/26.
//

#ifndef SFML_TEST_GAME_H
#define SFML_TEST_GAME_H
#include "../Map/Map.h"
#include "../Player/Player.h"
#include "../ViewModule/View/View.h"

class Game
{
    Player m_player;
    Map m_map;
    View m_view;
    sf::Clock m_clock;

    bool m_isRunning{};
public:
    Game();

    void StartGame();
    void EndGame();
};

#endif // SFML_TEST_GAME_H
