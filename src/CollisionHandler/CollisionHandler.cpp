//
// Created by x3r1x on 10/21/26.
//

#include "CollisionHandler.hpp"

#include "../ViewModule/View/View.hpp"
#include "../constants.hpp"
#include "CollisionType.hpp"

using namespace std;

CollisionHandler::CollisionHandler(Player &player, Map &map, View &view)
    : m_player(player), m_map(map), m_view(view)
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

    const auto interactableTiles = m_map.GetNearbyInteractableTiles(bounds);
    bool canInteract = false;

    for (const auto &tileRect : interactableTiles)
    {
        if (bounds.findIntersection(tileRect))
        {
            m_map.SetInteractingTile(tileRect);
            m_interactingTile = tileRect;
            canInteract = true;
        }
    }

    m_isInteracting = canInteract;
    m_map.SetInteraction(canInteract);
}

void CollisionHandler::HandlePlayerMapCollision()
{
    HandlePlayerMapBump();
    HandlePlayerMapInteraction();
}

void CollisionHandler::Interact(bool& isNoteOpen) const
{
    if (!m_isInteracting)
    {
        return;
    }

    const TileType tileType =
        m_map.GetTile(m_interactingTile.position.x, m_interactingTile.position.y);

    const int x = static_cast<int>(m_interactingTile.position.x / TILE_SIZE);
    const int y = static_cast<int>(m_interactingTile.position.y / TILE_SIZE);

    switch (tileType)
    {
    case TileType::LeftDoorClosed:
        m_map.SetTile(x, y, TileType::LeftDoorOpen);
        m_map.SetTile(x + 1, y, TileType::RightDoorOpen);

        break;
    case TileType::RightDoorClosed:
        m_map.SetTile(x - 1, y, TileType::LeftDoorOpen);
        m_map.SetTile(x, y, TileType::RightDoorOpen);

        break;
    case TileType::LeftDoorOpen:
    case TileType::RightDoorOpen:
        m_map.ChangeRoom(Room::Electrical);
        m_player.SetPosition(ELECTRICAL_SPAWN_POSITION);
        m_view.SetMapPixelSize({ENNARD_ROOM_WIDTH * TILE_SIZE, ENNARD_ROOM_HEIGHT * TILE_SIZE});

        break;
    case TileType::Key:
        m_map.SetTile(x, y, TileType::CollectedKey);

        break;
    case TileType::Note:
        m_map.SetTile(x, y, TileType::CollectedNote);
        isNoteOpen = true;

        break;
    default:
        break;
    }
}