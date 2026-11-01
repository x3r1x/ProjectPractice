//
// Created by x3r1x on 10/20/26.
//

#include "Game.hpp"

Game::Game()
    : m_collisionHandler(m_player, m_map), m_view(m_map.GetView(), m_player)
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

        EventListener::HandleInput(m_player, elapsedTime);

        m_collisionHandler.HandlePlayerMapCollision();

        m_view.UpdateCamera(m_player.GetPosition());
        m_view.DrawObjects();
    }
}

void Game::EndGame()
{
    m_isRunning = false;
}