//
// Created by x3r1x on 10/21/26.
//

#include "CollisionHandler.hpp"

#include "../Entity/Player/Player.hpp"
#include "../GameConstants.hpp"
#include "../ViewModule/View/View.hpp"
#include "CollisionType.hpp"

using namespace std;

CollisionHandler::CollisionHandler(Player &player, std::vector<std::unique_ptr<Enemy>> &enemies,
                                   Map &map, View &view)
    : m_player(player), m_enemies(enemies), m_map(map), m_view(view)
{
}

void CollisionHandler::HandlePlayerMapBumpByX(
    const std::vector<sf::FloatRect> &collidableTiles) const
{
    sf::FloatRect bounds = m_player.GetView().GetBounds();
    const sf::Vector2f position = m_player.GetPosition();
    const sf::Vector2f velocity = m_player.GetVelocity();

    bounds.position.y += EPSILON * 5000;
    bounds.size.y -= EPSILON * 10000;

    for (const auto &tileRect : collidableTiles)
    {
        const auto tileType = m_map.GetTile(tileRect.position.x, tileRect.position.y);
        const auto collisionType = GetCollisionType(tileType);

        if (bounds.findIntersection(tileRect) && collisionType == CollisionType::Bump &&
            tileType == TileType::Solid)
        {
            if (velocity.x > 0)
            {
                m_player.SetPosition(
                    {tileRect.position.x - bounds.size.x / 2 - EPSILON, position.y});
            }
            else if (velocity.x < 0)
            {
                m_player.SetPosition(
                    {tileRect.position.x + tileRect.size.x + bounds.size.x / 2 + EPSILON,
                     position.y});
            }

            m_player.SetVelocity({0, velocity.y});
            break;
        }
    }
}

void CollisionHandler::HandleEnemiesMapCollision() const
{
    for (auto &enemy : m_enemies)
    {
        const auto collidableTiles = m_map.GetNearbyCollidableTiles(enemy->GetBounds());
        HandleEnemyMapCollisionByX(*enemy, collidableTiles);
        HandleEnemyMapCollisionByY(*enemy, collidableTiles);
        enemy->ClampToZone();
    }
}

Enemy *CollisionHandler::GetCollidingEnemy() const
{
    const sf::FloatRect playerBounds = m_player.GetView().GetBounds();

    for (const auto &enemy : m_enemies)
    {
        if (playerBounds.findIntersection(enemy->GetBounds()))
        {
            return enemy.get();
        }
    }

    return nullptr;
}

void CollisionHandler::HandlePlayerMapBumpByY(
    const std::vector<sf::FloatRect> &collidableTiles) const
{
    m_player.SetGround(false);
    sf::FloatRect bounds = m_player.GetView().GetBounds();
    const auto velocity = m_player.GetVelocity();
    const auto position = m_player.GetPosition();

    bounds.position.x += EPSILON * 5000;
    bounds.size.x -= EPSILON * 10000;

    for (const auto &tileRect : collidableTiles)
    {
        const auto tileType = m_map.GetTile(tileRect.position.x, tileRect.position.y);
        const auto collisionType = GetCollisionType(tileType);

        if (bounds.findIntersection(tileRect) && collisionType == CollisionType::Bump &&
            !(tileType == TileType::Platform && velocity.y <= 0))
        {
            if (velocity.y > 0)
            {
                m_player.SetPosition(
                    {position.x, tileRect.position.y - bounds.size.y / 2 - EPSILON});
                m_player.SetGround(true);
            }
            else if (velocity.y < 0)
            {
                m_player.SetPosition({position.x, tileRect.position.y + tileRect.size.y +
                                                      bounds.size.y / 2 + EPSILON});
            }

            m_player.SetVelocity({velocity.x, 0});
            break;
        }
    }
}

void CollisionHandler::HandleEnemyMapCollisionByX(
    Enemy &enemy, const std::vector<sf::FloatRect> &collidableTiles) const
{
    sf::FloatRect bounds = enemy.GetBounds();
    const sf::Vector2f position = enemy.GetPosition();
    const sf::Vector2f velocity = enemy.GetVelocity();

    bounds.position.y += EPSILON * 5000;
    bounds.size.y -= EPSILON * 10000;

    for (const auto &tileRect : collidableTiles)
    {
        const auto tileType = m_map.GetTile(tileRect.position.x, tileRect.position.y);
        const auto collisionType = GetCollisionType(tileType);

        if (bounds.findIntersection(tileRect) && collisionType == CollisionType::Bump &&
            tileType == TileType::Solid)
        {
            if (velocity.x > 0)
            {
                enemy.SetPosition({tileRect.position.x - bounds.size.x / 2 - EPSILON, position.y});
                enemy.SetVelocity({0, velocity.y});
                enemy.CollideWithWall(true);
            }
            else if (velocity.x < 0)
            {
                enemy.SetPosition(
                    {tileRect.position.x + tileRect.size.x + bounds.size.x / 2 + EPSILON,
                     position.y});
                enemy.SetVelocity({0, velocity.y});
                enemy.CollideWithWall(false);
            }
            break;
        }
    }
}

void CollisionHandler::HandleEnemyMapCollisionByY(
    Enemy &enemy, const std::vector<sf::FloatRect> &collidableTiles) const
{
    enemy.SetGround(false);
    sf::FloatRect bounds = enemy.GetBounds();
    const auto velocity = enemy.GetVelocity();
    const auto position = enemy.GetPosition();

    bounds.position.x += EPSILON * 5000;
    bounds.size.x -= EPSILON * 10000;

    for (const auto &tileRect : collidableTiles)
    {
        const auto tileType = m_map.GetTile(tileRect.position.x, tileRect.position.y);
        const auto collisionType = GetCollisionType(tileType);

        if (bounds.findIntersection(tileRect) && collisionType == CollisionType::Bump &&
            !(tileType == TileType::Platform && velocity.y <= 0))
        {
            if (velocity.y > 0)
            {
                enemy.SetPosition({position.x, tileRect.position.y - bounds.size.y / 2 - EPSILON});
                enemy.SetGround(true);
            }
            else if (velocity.y < 0)
            {
                enemy.SetPosition({position.x, tileRect.position.y + tileRect.size.y +
                                                   bounds.size.y / 2 + EPSILON});
            }

            enemy.SetVelocity({velocity.x, 0});
            break;
        }
    }
}

void CollisionHandler::HandlePlayerMapBump() const
{
    const auto collidableTiles = m_map.GetNearbyCollidableTiles(m_player.GetView().GetBounds());

    HandlePlayerMapBumpByX(collidableTiles);
    HandlePlayerMapBumpByY(collidableTiles);
}

void CollisionHandler::HandlePlayerMapInteraction()
{
    sf::FloatRect bounds = m_player.GetView().GetBounds();

    bounds.position.x -= INTERACTION_DISTANCE;
    bounds.position.y -= INTERACTION_DISTANCE;
    bounds.size.x += INTERACTION_DISTANCE * 2;
    bounds.size.y += INTERACTION_DISTANCE * 2;

    m_currentInteractable = m_map.GetInteractableAt(bounds);

    if (m_currentInteractable != nullptr)
    {
        m_map.SetInteraction(true);
        m_map.SetInteractingObject(*m_currentInteractable);
    }
    else
    {
        m_map.SetInteraction(false);
    }
}

void CollisionHandler::HandlePlayerMapCollision()
{
    HandlePlayerMapBump();
    HandlePlayerMapInteraction();
}

void CollisionHandler::Interact(bool &isNoteOpen, std::string &noteText)
{
    if (m_currentInteractable == nullptr || !m_currentInteractable->CanInteract())
    {
        return;
    }

    const Room previousRoom = m_map.GetRoom();
    InteractionContext context{m_player, m_map, m_view, isNoteOpen, noteText};
    m_currentInteractable->Interact(context);

    if (m_map.GetRoom() != previousRoom || !m_currentInteractable->CanInteract())
    {
        m_currentInteractable = nullptr;
        m_map.SetInteraction(false);
    }
}
