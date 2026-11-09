//
// Created by x3r1x on 10/20/26.
//

#include "Game.hpp"

Game::Game(sf::RenderWindow &window)
    : m_view(window, m_map.GetView(), m_player), m_collisionHandler(m_player, m_map, m_view)
{
}

void Game::HandleEvent(const sf::Event &event)
{
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
}