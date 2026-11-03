//
// Created by x3r1x on 11/3/26.
//

#ifndef SFML_TEST_STATEMANAGER_HPP
#define SFML_TEST_STATEMANAGER_HPP
#pragma once
#include <cstdint>

#include <SFML/Graphics/RenderWindow.hpp>

enum class AppState: uint8_t
{
    MainMenu = 0,
    Options = 1,
    Tutorial = 2,
    Newspaper = 3,
    GamePlaying = 4,
    GamePaused = 5,
    Jumpscare = 6,
    GameLost = 7,
    BadEnding = 8,
    GoodEnding = 9
};

class StateManager
{
    AppState m_state;
    sf::RenderWindow m_window;
public:
    StateManager();

    AppState GetState() const;

    void GoToMainMenu();
    void ShowOptions();
    void ShowTutorial();
    void GoToNewspaper();
    void GoToGame(); //?
    void PauseGame();
    void ShowJumpscare();
    void GoToGameLost();
    void GoToBadEnding();
    void GoToGoodEnding();
};

#endif // SFML_TEST_STATEMANAGER_HPP
