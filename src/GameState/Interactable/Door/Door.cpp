//
// Created by gleb.ryzhov on 11/11/26.
//

#include "Door.hpp"

#include "../../Entity/Map/Map.hpp"
#include "../../Entity/Map/TileType.hpp"
#include "../../Entity/Player/Player.hpp"
#include "../../GameConstants.hpp"
#include "../../ViewModule/View/View.hpp"

Door::Door(const sf::Vector2i position, const Room targetRoom, const sf::Vector2f spawnPosition,
           const bool isClosed)
    : IInteractable(position), m_targetRoom(targetRoom), m_spawnPosition(spawnPosition),
      m_isClosed(isClosed)
{
}

sf::FloatRect Door::GetBounds() const
{
    const sf::Vector2i position = GetPosition();
    return {
        {static_cast<float>(position.x * TILE_SIZE), static_cast<float>(position.y * TILE_SIZE)},
        {static_cast<float>(TILE_SIZE * 2), static_cast<float>(TILE_SIZE)}};
}

sf::Vector2f Door::GetRoomPixelSize(const Room room)
{
    switch (room)
    {
    case Room::Main:
        return {MAIN_ROOM_WIDTH * TILE_SIZE, MAIN_ROOM_HEIGHT * TILE_SIZE};
    case Room::CircusBaby:
        return {CIRCUS_BABY_ROOM_WIDTH * TILE_SIZE, CIRCUS_BABY_ROOM_HEIGHT * TILE_SIZE};
    case Room::Electrical:
        return {ELECTRICAL_ROOM_WIDTH * TILE_SIZE, ELECTRICAL_ROOM_HEIGHT * TILE_SIZE};
    case Room::Ennard:
        return {ENNARD_ROOM_WIDTH * TILE_SIZE, ENNARD_ROOM_HEIGHT * TILE_SIZE};
    default:
        return {0.0, 0.0};
    }
}

void Door::Interact(InteractionContext &context)
{
    if (!CanInteract())
    {
        return;
    }

    if (m_isClosed)
    {
        m_isClosed = false;

        const sf::Vector2i position = GetPosition();
        context.map.SetTile(position.x, position.y, TileType::LeftDoorOpen);
        context.map.SetTile(position.x + 1, position.y, TileType::RightDoorOpen);

        return;
    }

    context.player.SetPosition(m_spawnPosition);
    context.view.SetMapPixelSize(GetRoomPixelSize(m_targetRoom));
    context.map.ChangeRoom(m_targetRoom);
}

bool Door::CanInteract() const
{
    return true;
}
