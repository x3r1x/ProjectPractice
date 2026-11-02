//
// Created by x3r1x on 10/20/26.
//

#include "Map.hpp"

#include <algorithm>

#include "../../CollisionHandler/CollisionType.hpp"
#include "../../constants.hpp"

// capital letter means that whatever lays inside that tile has benn used
// . = empty space
// # = solid block
// p = platform
// n = note
// k = key
// l = left door
// r = right door
const std::vector TILE_ABBREVIATIONS = {'.', '#', 'p', 'n', 'N', 'k', 'K', 'l', 'r', 'L', 'R'};

const std::string MAP_STRUCTURE = "####################"
                                  "#..................#"
                                  "#..................#"
                                  "#..................#"
                                  "#..................#"
                                  "#..................#"
                                  "#..................#"
                                  "#..................#"
                                  "#..................#"
                                  "#..................#"
                                  "#..................#"
                                  "#..................#"
                                  "#...LR.............#"
                                  "#..pppp............#"
                                  "#..................#"
                                  "#.............lr...#"
                                  "#............####..#"
                                  "#..................#"
                                  "#...k..............#"
                                  "#...###............#"
                                  "#.............N....#"
                                  "#...........ppp....#"
                                  "#..................#"
                                  "#..................#"
                                  "#......K.....n.....#"
                                  "####################";

Map::Map() : m_view(MAP_HEIGHT, MAP_WIDTH)
{
    m_width = MAP_WIDTH;
    m_height = MAP_HEIGHT;

    m_grid.assign(m_width * m_height, TileType::Empty);

    for (int i = 0; i < m_width; i++)
    {
        for (int j = 0; j < m_height; j++)
        {
            SetTile(i, j, GetTileType(MAP_STRUCTURE[j * m_width + i]));
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

void Map::SetInteractingTile(const sf::FloatRect tileRect)
{
    const TileType tileType = GetTile(tileRect.position.x, tileRect.position.y);

    m_view.SetInteractionPosition(tileRect, tileType);
}

void Map::SetTile(const int worldX, const int worldY, const TileType type)
{
    if (worldX < m_width && worldY < m_height)
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

std::vector<sf::FloatRect> Map::GetNearbyInteractableTiles(const sf::FloatRect &bounds) const
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

            if (collisionType == CollisionType::Interaction)
            {
                nearbyTiles.emplace_back(sf::Vector2f(c * TILE_SIZE, r * TILE_SIZE),
                                         sf::Vector2f(TILE_SIZE, TILE_SIZE));
            }
        }
    }

    return nearbyTiles;
}