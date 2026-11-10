//
// Created by x3r1x on 11/3/26.
//

#ifndef SFML_TEST_STATEMANAGER_HPP
#define SFML_TEST_STATEMANAGER_HPP
#pragma once

#include <memory>
#include <optional>

#include <SFML/Graphics/RenderWindow.hpp>

#include "../GameState/Game/Game.hpp"
#include "../IState.hpp"
#include "../MenuState/MainMenu/MainMenu.hpp"

enum class AppState: uint8_t
{
    MainMenu = 0,
    Options = 1,
    Tutorial = 2,
    Newspaper = 3,
    GamePlaying = 4,
    GamePaused = 5,
    JumpScare = 6,
    GameLost = 7,
    BadEnding = 8,
    GoodEnding = 9
};

class StateManager
{
    sf::RenderWindow m_window;

    std::unique_ptr<IState> m_stateObject;
    AppState m_state = AppState::MainMenu;
    std::optional<AppState> m_pendingState;

    void HandleEvents(const sf::Event &event);
    void Update(float elapsedTime) const;
    void Draw();
    void StartGame();
    void GoToMenu();
    void ApplyStateChange();
    void SetGamePaused(bool paused);
public:
    StateManager();

    AppState GetState() const;
    void Run();
};

#endif // SFML_TEST_STATEMANAGER_HPP
