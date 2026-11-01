//
// Created by x3r1x on 10/20/26.
//

#include "Map.hpp"

#include <algorithm>

#include "../../constants.hpp"

Map::Map() : m_view(MAP_HEIGHT, MAP_WIDTH)
{
    m_width = MAP_WIDTH;
    m_height = MAP_HEIGHT;

    m_grid.assign(m_width * m_height, TileType::Empty);

    for (int x = 0; x < m_width; x++)
    {
        SetTile(x, 0, TileType::Solid);
        SetTile(x, m_height - 1, TileType::Solid);
    }
    for (int y = 0; y < m_height; y++)
    {
        SetTile(0, y, TileType::Solid);
        SetTile(m_width - 1, y, TileType::Solid);
    }

    for (int x = 3; x <= 8; x++)
    {
        SetTile(x, 15, TileType::Platform);
    }

    for (int x = 12; x <= 18; x++)
    {
        SetTile(x, 12, TileType::Platform);
    }

    for (int x = 22; x <= 27; x++)
    {
        SetTile(x, 8, TileType::Platform);
    }

    SetTile(26, 7, TileType::Solid);

    for (int x = 4; x <= 8; x++)
    {
        SetTile(x, 6, TileType::Solid);
    }

    SetTile(10, MAP_HEIGHT - 2, TileType::Solid);

    m_view.SetGrid(m_grid);
}

MapView &Map::GetView()
{
    return m_view;
}

void Map::SetTile(const int worldX, const int worldY, const TileType type)
{
    if (worldX < m_width && worldY < m_height) {
        m_grid[worldY * m_width + worldX] = type;
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
    const int maxCol = std::clamp(static_cast<int>((bounds.position.x + bounds.size.x) / TILE_SIZE), 0, m_width - 1);
    const int minRow = std::clamp(static_cast<int>(bounds.position.y / TILE_SIZE), 0, m_height - 1);
    const int maxRow = std::clamp(static_cast<int>((bounds.position.y + bounds.size.y) / TILE_SIZE), 0, m_height - 1);

    for (int r = minRow; r <= maxRow; r++)
    {
        for (int c = minCol; c <= maxCol; c++)
        {
            if (m_grid[r * m_width + c] != TileType::Empty)
            {
                nearbyTiles.emplace_back(
                    sf::Vector2f(c * TILE_SIZE, r * TILE_SIZE),
                    sf::Vector2f(TILE_SIZE, TILE_SIZE)
                );
            }
        }
    }

    return nearbyTiles;
}