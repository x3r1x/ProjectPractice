//
// Created by gleb.ryzhov on 11/11/26.
//

#include "Key.hpp"
#include "../../Entity/Map/Map.hpp"
#include "../../Entity/Map/TileType.hpp"
#include "../../Entity/Player/Player.hpp"

Key::Key(const sf::Vector2i position) : IInteractable(position)
{
}

void Key::Interact(InteractionContext &context)
{
    if (!CanInteract())
    {
        return;
    }

    m_isCollected = true;

    const sf::Vector2i position = GetPosition();
    context.map.SetTile(position.x, position.y, TileType::CollectedKey);
    context.player.AddKey();
}

bool Key::CanInteract() const
{
    return !m_isCollected;
}
