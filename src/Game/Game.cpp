//
// Created by x3r1x on 10/20/26.
//

#include "Game.h"

Game::Game()
    : m_collisionHandler(m_player, m_map), m_hud(m_player), m_view(m_map.GetView(), m_player.GetView(), m_hud)
{
}

Game::~Game()
{
    m_isRunning = false;
}

void Game::StartGame()
{
    m_isRunning = true;

    while (m_view.GetWindow().isOpen() && m_isRunning)
    {
        EventListener::HandleEvents(m_view.GetWindow());

        const float elapsedTime = m_clock.restart().asSeconds();

        m_eventListener.HandleInput(m_player, elapsedTime);

        m_collisionHandler.HandlePlayerMapCollision();

        m_view.UpdateCamera(m_player.GetPosition());
        m_view.DrawObjects();
    }
}

void Game::EndGame()
{
    m_isRunning = false;
}