//
// Created by x3r1x on 10/21/26.
//

#include "CollisionHandler.hpp"

#include <iostream>

#include "../constants.hpp"

using namespace std;

CollisionHandler::CollisionHandler(Player &player, Map &map) : m_player(player), m_map(map) {}

void CollisionHandler::HandlePlayerMapCollisionByX() const
{
    sf::FloatRect bounds = m_player.GetView().GetBounds();
    const sf::Vector2f position = m_player.GetPosition();
    const sf::Vector2f velocity = m_player.GetVelocity();

    bounds.position.y += EPSILON * 500;
    bounds.size.y -= EPSILON * 1000;

    for (const auto &tileRect : m_map.GetNearbyCollidableTiles(bounds))
    {
        const auto tileType = m_map.GetTile(tileRect.position.x, tileRect.position.y);

        if (bounds.findIntersection(tileRect) && tileType == TileType::Solid)
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

void CollisionHandler::HandlePlayerMapCollisionByY() const
{
    m_player.SetGround(false);
    sf::FloatRect bounds = m_player.GetView().GetBounds();
    const auto velocity = m_player.GetVelocity();
    const auto position = m_player.GetPosition();

    bounds.position.x += EPSILON * 500;
    bounds.size.x -= EPSILON * 1000;

    for (const auto &tileRect : m_map.GetNearbyCollidableTiles(bounds))
    {
        const TileType tileType = m_map.GetTile(tileRect.position.x, tileRect.position.y);

        if (bounds.findIntersection(tileRect) && !(tileType == TileType::Platform && velocity.y <= 0))
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

void CollisionHandler::HandlePlayerMapCollision() const
{
    HandlePlayerMapCollisionByX();
    HandlePlayerMapCollisionByY();
}

bool CollisionHandler::IntersectsX(const sf::FloatRect a, const sf::FloatRect b)
{
    return a.position.x < b.position.x + b.size.x && a.position.x + a.size.x > b.position.x;
}

bool CollisionHandler::IntersectsY(const sf::FloatRect a, const sf::FloatRect b)
{
    return a.position.y < b.position.y + b.size.y && a.position.y + a.size.y > b.position.y;
}