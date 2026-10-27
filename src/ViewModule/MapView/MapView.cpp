//
// Created by x3r1x on 10/20/26.
//

#include "MapView.hpp"

#include <iostream>

#include "../../constants.hpp"

enum class TileType : uint8_t;
constexpr auto PATH_TO_SPRITE = "../assets/Tiles.png";

MapView::MapView(const int height, const int width) : m_sprite(m_texture)
{
    m_height = height;
    m_width = width;

    if (!m_texture.loadFromFile(PATH_TO_SPRITE))
    {
        std::cerr << "Could not load Tiles.png" << std::endl;
        return;
    }
}

void MapView::SetGrid(const std::vector<TileType> &grid)
{
    m_grid = grid;
}

void MapView::Draw(sf::RenderWindow &window)
{
    for (int row = 0; row < m_height; row++)
    {
        for (int col = 0; col < m_width; col++)
        {
            const int index = row * m_width + col;
            TileType type = m_grid[index];

            if (type == TileType::Empty)
            {
                continue;
            }

            auto x = static_cast<float>(col * TILE_SIZE);
            auto y = static_cast<float>(row * TILE_SIZE);

            const int tileSetIndex = static_cast<int>(type);
            sf::IntRect textureRect({tileSetIndex * TILE_SIZE, 0},
                                    {TILE_SIZE, TILE_SIZE});
            
            m_sprite.setTextureRect(textureRect);
            m_sprite.setPosition({x, y});

            window.draw(m_sprite);
        }
    }
}