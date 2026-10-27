//
// Created by x3r1x on 10/20/26.
//

#include "Map.hpp"

#include "../../constants.hpp"

Map::Map()
{
    m_width = 30;
    m_height = 20;

    m_grid.assign(m_width * m_height, TileType::Empty);

    for (int x = 0; x < m_width; x++) {
        SetTile(x, 0, TileType::Solid);
        SetTile(x, m_height - 1, TileType::Solid);
    }
    for (int y = 0; y < m_height; y++) {
        SetTile(0, y, TileType::Solid);
        SetTile(m_width - 1, y, TileType::Solid);
    }

    for (int x = 3; x <= 8; x++) {
        SetTile(x, 15, TileType::Platform);
    }

    for (int x = 12; x <= 18; x++) {
        SetTile(x, 12, TileType::Platform);
    }

    for (int x = 22; x <= 27; x++) {
        SetTile(x, 8, TileType::Platform);
    }

    for (int x = 4; x <= 8; x++) {
        SetTile(x, 6, TileType::Solid);
    }
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
    if (worldX < 0 || worldY < 0 || worldY > m_height * TILE_SIZE || worldY > m_width * TILE_SIZE)
    {
        return TileType::Empty;
    }

    const int col = static_cast<int>(worldX / TILE_SIZE);
    const int row = static_cast<int>(worldY / TILE_SIZE);

    const int index = row * m_width + col;

    return m_grid[index];
}