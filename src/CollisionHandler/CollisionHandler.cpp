//
// Created by x3r1x on 10/21/26.
//

#include "CollisionHandler.hpp"



CollisionHandler::CollisionHandler(Player &player, Map &map) : m_player(player), m_map(map) {}

void CollisionHandler::HandlePlayerMapCollision() const
{
    const sf::Vector2f oldPosition = m_player.GetPosition();
    const sf::Vector2f playerBounds = m_player.GetBounds();
    const sf::Vector2f mapBounds = m_map.GetBounds();

    sf::Vector2f position = oldPosition;
    sf::Vector2f velocity = m_player.GetVelocity();

    if (position.x < 0.f)
    {
        position.x = 0.f;
    }
    else if (position.x + playerBounds.x > mapBounds.x)
    {
        position.x = mapBounds.x - playerBounds.x;
    }

    if (position.y < 0.f)
    {
        position.y = 0.f;
    }
    else if (position.y + playerBounds.y > mapBounds.y)
    {
        position.y = mapBounds.y - playerBounds.y;
    }


    if (position.x != oldPosition.x)
    {
        velocity.x = 0.f;
    }

    if (position.y != oldPosition.y)
    {
        velocity.y = 0.f;
    }

    m_player.SetPosition(position);
}