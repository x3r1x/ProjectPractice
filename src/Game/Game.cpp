//
// Created by x3r1x on 10/20/26.
//

#include "Game.h"

Game::Game() : m_view(m_map.GetView(), m_player.GetView())
{
}

void Game::StartGame()
{
    m_isRunning = true;

    while (m_view.GetWindow().isOpen() && m_isRunning)
    {
        while (const std::optional event = m_view.GetWindow().pollEvent())
        {
            if (event->is<sf::Event::Closed>() ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            {
                m_view.GetWindow().close();
                m_isRunning = false;
            }
        }

        const float elapsedTime = m_clock.restart().asSeconds();
        m_player.Update(elapsedTime);

        m_view.DrawObjects();
    }
}

void Game::EndGame()
{
    m_isRunning = false;
}