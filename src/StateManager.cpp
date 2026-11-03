//
// Created by x3r1x on 11/3/26.
//

#include "StateManager.hpp"

StateManager::StateManager()
{
    m_state = AppState::MainMenu;
    m_window = sf::RenderWindow()

    GoToMainMenu();
}

AppState StateManager::GetState() const
{
    return m_state;
}

void StateManager::GoToMainMenu()
{

}

void StateManager::ShowOptions()
{

}

void StateManager::ShowTutorial()
{

}

void StateManager::GoToNewspaper()
{

}

void StateManager::GoToGame()
{

}

void StateManager::PauseGame()
{

}

void StateManager::ShowJumpscare()
{

}

void StateManager::GoToGameLost()
{

}

void StateManager::GoToBadEnding()
{

}

void StateManager::GoToGoodEnding()
{

}