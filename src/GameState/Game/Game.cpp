//
// Created by x3r1x on 10/20/26.
//

#include "Game.hpp"

#include <utility>

Game::Game(sf::RenderWindow& window, std::function<void()> onContinueGame, std::function<void()> onExitGame)
    : m_view(window, m_map.GetView(), m_player), m_collisionHandler(m_player, m_map, m_view), m_onContinueGame(std::move(onContinueGame)), m_onExitGame(std::move(onExitGame))
{
}

void Game::SetAppPause(const bool isPaused)
{
    m_isAppPaused = isPaused;
}

void Game::HandleEvent(const sf::Event &event)
{
    if (m_isAppPaused)
    {
        if (m_view.IsExitClicked(event))
        {
            m_onExitGame();
        }

        if (m_view.IsContinueClicked(event))
        {
            m_onContinueGame();
        }
        return;
    }

    EventListener::HandleEvents(event, m_collisionHandler, m_isNoteOpen, m_currentNoteText);
    m_view.SetIsShowingNote(m_isNoteOpen);
    m_view.SetNoteText(m_currentNoteText);
}

void Game::Update(const float deltaTime)
{
    if (m_isNoteOpen)
    {
        return;
    }
    EventListener::HandleInput(m_player, deltaTime);
    m_collisionHandler.HandlePlayerMapCollision();
    m_view.UpdateCamera(m_player.GetPosition());
}

void Game::Draw()
{
    m_view.DrawObjects();

    if (m_isAppPaused)
    {
        m_view.DrawPauseMenu();
    }
}
