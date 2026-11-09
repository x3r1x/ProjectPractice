//
// Created by x3r1x on 10/20/26.
//

#ifndef SFML_TEST_GAME_H
#define SFML_TEST_GAME_H
#pragma once
#include "../../IState.hpp"
#include "../CollisionHandler/CollisionHandler.hpp"
#include "../Entity/Map/Map.hpp"
#include "../Entity/Player/Player.hpp"
#include "../EventListener/EventListener.hpp"
#include "../ViewModule/View/View.hpp"

class Game: public IState
{
    Player m_player;
    Map m_map;
    View m_view;
    CollisionHandler m_collisionHandler;

    bool m_isNoteOpen = false;
    std::string m_currentNoteText;
public:
    explicit Game(sf::RenderWindow& window);

    void HandleEvent(const sf::Event& event) override;
    void Update(float deltaTime) override;
    void Draw() override;
};

#endif // SFML_TEST_GAME_H
