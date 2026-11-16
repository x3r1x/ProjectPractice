//
// Created by x3r1x on 10/20/26.
//

#include "Map.hpp"

#include <algorithm>

#include "../../CollisionHandler/CollisionType.hpp"
#include "../../GameConstants.hpp"
#include "../../Interactable/Door/Door.hpp"
#include "../../Interactable/Key/Key.hpp"
#include "../../Interactable/Note/Note.hpp"

// capital letter means that whatever lays inside that tile has been used
// . = empty space
// # = solid block
// p = platform
// n = note
// k = key
// l = left door
// r = right door
const std::vector TILE_ABBREVIATIONS = {'.', '#', 'p', 'n', 'N', 'k', 'K', 'l', 'r', 'L', 'R'};

Map::Map()
{
    ChangeRoom(Room::Main);
}

Room Map::GetRoom() const
{
    return m_room;
}

void Map::ChangeToMainRoom()
{
    m_width = MAIN_ROOM_WIDTH;
    m_height = MAIN_ROOM_HEIGHT;

    // DOORS
    m_interactableObjects.push_back(
        std::make_unique<Door>(sf::Vector2i{9, 12}, Room::Electrical, ELECTRICAL_SPAWN_POSITION, true));
    m_interactableObjects.push_back(
        std::make_unique<Door>(sf::Vector2i{2, 39}, Room::Ennard, ENNARD_ROOM_SPAWN_POSITION, true));
    m_interactableObjects.push_back(
        std::make_unique<Door>(sf::Vector2i{16, 39}, Room::CircusBaby, CIRCUS_BABY_SPAWN_POSITION, true));

    // NOTES
    // left at spawn
    m_interactableObjects.push_back(
        std::make_unique<Note>(sf::Vector2i{6, 39}, "NOTE 1\nHey!"));

    // right at spawn
    m_interactableObjects.push_back(
        std::make_unique<Note>(sf::Vector2i{13, 39}, "NOTE 2\nHello!"));

    // left near spawn
    m_interactableObjects.push_back(
        std::make_unique<Note>(sf::Vector2i{1, 36}, "NOTE 3\nGoodbye!"));

    // right near spawn
    m_interactableObjects.push_back(
        std::make_unique<Note>(sf::Vector2i{18, 36}, "NOTE 4\nBye!"));

    // funtime freddy room
    m_interactableObjects.push_back(
        std::make_unique<Note>(sf::Vector2i{5, 1},
                               "NOTE 5\nSay hello to Funtime Freddy,\nas well as his BonBon!"));

    // bidybab and electrobab room
    m_interactableObjects.push_back(
        std::make_unique<Note>(sf::Vector2i{14, 21},
                               "NOTE 6\nSay hello to Bidybab and\nElectrobab duo!"));
}

void Map::ChangeToEnnardRoom()
{
    m_width = ENNARD_ROOM_WIDTH;
    m_height = ENNARD_ROOM_HEIGHT;

    // DOORS
    m_interactableObjects.push_back(
        std::make_unique<Door>(sf::Vector2i{5, 8}, Room::Main, PLAYER_START_POSITION, false));
}

void Map::ChangeToCircusBabyRoom()
{
    m_width = CIRCUS_BABY_ROOM_WIDTH;
    m_height = CIRCUS_BABY_ROOM_HEIGHT;

    // DOORS
    m_interactableObjects.push_back(
        std::make_unique<Door>(sf::Vector2i{9, 14}, Room::Main, MAIN_ROOM_FROM_CIRCUS_SPAWN_POSITION, false));

    // NOTES
    m_interactableObjects.push_back(
        std::make_unique<Note>(sf::Vector2i{11, 3}, "NOTE 7\nSay hello to CIIIIIRCUS BABY!"));
}

void Map::ChangeToElectricalRoom()
{
    m_width = ELECTRICAL_ROOM_WIDTH;
    m_height = ELECTRICAL_ROOM_HEIGHT;

    // DOORS
    m_interactableObjects.push_back(
        std::make_unique<Door>(sf::Vector2i{1, 8}, Room::Main, MAIN_ROOM_FROM_ELECTRICAL_SPAWN_POSITION, false));

    // NOTES
    m_interactableObjects.push_back(
        std::make_unique<Note>(sf::Vector2i{9, 2},
                               "NOTE 8\nSome secrets are gonna be \nrevealed here...\nIdk which ones, so...\n\n\nCOMING SOON!"));
}

void Map::ReadRoom(const char *structure)
{
    m_grid.assign(m_width * m_height, TileType::Empty);

    for (int i = 0; i < m_width; i++)
    {
        for (int j = 0; j < m_height; j++)
        {
            const TileType type = GetTileType(structure[j * m_width + i]);
            m_grid[j * m_width + i] = type;

            if (type == TileType::Key)
            {
                m_interactableObjects.push_back(std::make_unique<Key>(sf::Vector2i{i, j}));
            }
        }
    }

    m_view.SetGrid(m_grid);
}

TileType Map::GetTileType(const char tileAbbreviation)
{
    for (size_t i = 0; i < TILE_ABBREVIATIONS.size(); i++)
    {
        if (TILE_ABBREVIATIONS[i] == tileAbbreviation)
        {
            return static_cast<TileType>(i);
        }
    }

    return TileType::Empty;
}

MapView &Map::GetView()
{
    return m_view;
}

void Map::SetInteraction(const bool canInteract)
{
    m_view.SetCanInteract(canInteract);
}

void Map::SetInteractingObject(const IInteractable &interactable)
{
    m_view.SetInteractionPosition(interactable.GetPromptPosition());
}

void Map::SetTile(const int worldX, const int worldY, const TileType type)
{
    if (worldX >= 0 && worldY >= 0 && worldX < m_width && worldY < m_height)
    {
        m_grid[worldY * m_width + worldX] = type;
        m_view.SetGrid(m_grid);
    }
}

TileType Map::GetTile(const float worldX, const float worldY) const
{
    if (worldX < 0 || worldY < 0 || worldY > m_height * TILE_SIZE || worldX > m_width * TILE_SIZE)
    {
        return TileType::Empty;
    }

    const int col = static_cast<int>(worldX / TILE_SIZE);
    const int row = static_cast<int>(worldY / TILE_SIZE);

    const int index = row * m_width + col;

    return m_grid[index];
}

void Map::ChangeRoom(const Room room)
{
    m_interactableObjects.clear();

    m_room = room;
    const char *roomStructure = "";

    switch (room)
    {
    case Room::Main:
        ChangeToMainRoom();
        roomStructure = MAIN_ROOM_STRUCTURE;
        break;
    case Room::Ennard:
        ChangeToEnnardRoom();
        roomStructure = ENNARD_ROOM_STRUCTURE;
        break;
    case Room::CircusBaby:
        ChangeToCircusBabyRoom();
        roomStructure = CIRCUS_BABY_ROOM_STRUCTURE;
        break;
    case Room::Electrical:
        ChangeToElectricalRoom();
        roomStructure = ELECTRICAL_ROOM_STRUCTURE;
        break;
    default:
        break;
    }

    m_view.SetSize(m_width, m_height);
    ReadRoom(roomStructure);
}

std::vector<sf::FloatRect> Map::GetNearbyCollidableTiles(const sf::FloatRect &bounds) const
{
    std::vector<sf::FloatRect> nearbyTiles;

    const int minCol = std::clamp(static_cast<int>(bounds.position.x / TILE_SIZE), 0, m_width - 1);
    const int maxCol = std::clamp(static_cast<int>((bounds.position.x + bounds.size.x) / TILE_SIZE),
                                  0, m_width - 1);
    const int minRow = std::clamp(static_cast<int>(bounds.position.y / TILE_SIZE), 0, m_height - 1);
    const int maxRow = std::clamp(static_cast<int>((bounds.position.y + bounds.size.y) / TILE_SIZE),
                                  0, m_height - 1);

    for (int r = minRow; r <= maxRow; r++)
    {
        for (int c = minCol; c <= maxCol; c++)
        {
            const CollisionType collisionType = GetCollisionType(m_grid[r * m_width + c]);

            if (collisionType == CollisionType::Bump)
            {
                nearbyTiles.emplace_back(sf::Vector2f(c * TILE_SIZE, r * TILE_SIZE),
                                         sf::Vector2f(TILE_SIZE, TILE_SIZE));
            }
        }
    }

    return nearbyTiles;
}

IInteractable *Map::GetInteractableAt(const sf::FloatRect &bounds) const
{
    for (const auto &object : m_interactableObjects)
    {
        if (object->CanInteract() && bounds.findIntersection(object->GetBounds()))
        {
            return object.get();
        }
    }

    return nullptr;
}
