//
// Created by x3r1x on 10/20/26.
//

#include "MapView.hpp"

#include <iostream>

#include "../../constants.hpp"

enum class TileType : uint8_t;

constexpr auto PATH_TO_SPRITE = "../assets/png/Tiles.png";
constexpr auto FONT_PATH = "../assets/ttf/Euclid Circular B Bold.ttf";

MapView::MapView(const int height, const int width) : m_sprite(m_texture), m_text(m_font)
{
    m_height = height;
    m_width = width;

    if (!m_texture.loadFromFile(PATH_TO_SPRITE))
    {
        std::cerr << "Could not load Tiles.png" << std::endl;
        return;
    }

    if (!m_font.openFromFile(FONT_PATH))
    {
        std::cerr << "Error reading font!" << std::endl;
    }

    m_text.setString(INTERACTION_TEXT);
    m_text.setCharacterSize(INTERACTION_TEXT_SIZE);
    m_text.setFillColor(INTERACTION_TEXT_FILL_COLOR);

    const auto localTextBounds = m_text.getLocalBounds();
    m_text.setOrigin({
        localTextBounds.position.x + localTextBounds.size.x / 2,
        localTextBounds.position.y + localTextBounds.size.y / 2
    });
}

void MapView::SetCanInteract(const bool canInteract)
{
    m_canInteract = canInteract;
}

void MapView::SetInteractionPosition(const sf::FloatRect tileRect, const TileType type)
{
    if (type == TileType::LeftDoorClosed || type == TileType::LeftDoorOpen)
    {
        const float x = tileRect.position.x + tileRect.size.x;
        const float y = tileRect.position.y + tileRect.size.y / 2;

        m_text.setPosition({x, y});
        return;
    }

    if (type == TileType::RightDoorClosed || type == TileType::RightDoorOpen)
    {
        const float x = tileRect.position.x;
        const float y = tileRect.position.y + tileRect.size.y / 2;

        m_text.setPosition({x, y});
        return;
    }

    const float x = tileRect.position.x + tileRect.size.x / 2;
    const float y = tileRect.position.y + tileRect.size.y / 2;

    m_text.setPosition({x, y});
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

            auto x = static_cast<float>(col * TILE_SIZE);
            auto y = static_cast<float>(row * TILE_SIZE);

            const int tileSetIndex = static_cast<int>(type);
            sf::IntRect textureRect({tileSetIndex * TILE_SIZE, 0}, {TILE_SIZE, TILE_SIZE});

            m_sprite.setTextureRect(textureRect);
            m_sprite.setPosition({x, y});

            window.draw(m_sprite);
        }
    }

    if (m_canInteract)
    {
        window.draw(m_text);
    }
}