//
// Created by x3r1x on 10/20/26.
//

#include "Game.hpp"

#include <iostream>
#include <utility>

#include "../Entity/Enemy/EnemyFactory/EnemyFactory.hpp"

Game::Game(sf::RenderWindow &window, std::function<void()> onContinueGame,
           std::function<void()> onExitGame, std::function<void()> onPlayerDeath,
           std::function<void()> onGameEnd)
    : m_view(window, m_map.GetView(), m_player),
      m_collisionHandler(m_player, m_enemies, m_map, m_view),
      m_currentRoom(m_map.GetRoom()), m_onContinueGame(std::move(onContinueGame)),
      m_onExitGame(std::move(onExitGame)), m_onPlayerDeath(std::move(onPlayerDeath)),
      m_onGameEnd(std::move(onGameEnd))
{
    SpawnEnemiesForCurrentRoom();

    if (m_music.openFromFile("../assets/ost/Night Theme.mp3")) {
        m_music.setLooping(true);
        m_music.play();
    }
}

void Game::SpawnEnemiesForCurrentRoom()
{
    m_enemies.clear();

    for (const auto &spawn : m_map.GetEnemySpawns())
    {
        const sf::Vector2f worldPos{
            (spawn.spawnTile.x + 0.5f) * TILE_SIZE,
            (spawn.spawnTile.y + 0.5f) * TILE_SIZE};

        if (auto enemy = EnemyFactory::Create(spawn.type, worldPos, spawn.zoneTiles,
                                              m_onPlayerDeath, m_view.GetWindow().getSize()))
        {
            m_enemies.push_back(std::move(enemy));
        }
    }
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

    if (m_map.GetRoom() == Room::Ennard)
    {
        m_onGameEnd();
        return;
    }

    m_view.SetIsShowingNote(m_isNoteOpen);
    m_view.SetNoteText(m_currentNoteText);
}

void Game::Update(const float deltaTime)
{
    if (m_activeJumpScare != nullptr)
    {
        m_activeJumpScare->Update(deltaTime);
        return;
    }

    if (m_map.GetRoom() != m_currentRoom)
    {
        m_currentRoom = m_map.GetRoom();
        SpawnEnemiesForCurrentRoom();
    }

    if (m_isNoteOpen)
    {
        return;
    }

    EventListener::HandleInput(m_player, deltaTime);
    m_collisionHandler.HandlePlayerMapCollision();

    const EnemyContext context{m_player.GetPosition(), m_player.GetVelocity()};
    for (auto &enemy : m_enemies)
    {
        enemy->Update(context, deltaTime);
    }
    m_collisionHandler.HandleEnemiesMapCollision();

    if (Enemy *caughtBy = m_collisionHandler.GetCollidingEnemy())
    {
        m_activeJumpScare = &caughtBy->GetJumpScare();
        m_activeJumpScare->Play();
        return;
    }

    m_view.UpdateCamera(m_player.GetPosition());
}

void Game::Draw()
{
    m_view.DrawObjects();
    m_view.DrawEnemies(m_enemies);

    if (m_isAppPaused)
    {
        m_view.DrawPauseMenu();
    }

    if (m_activeJumpScare != nullptr && m_activeJumpScare->IsPlaying())
    {
        m_activeJumpScare->Draw(m_view.GetWindow());
    }
}