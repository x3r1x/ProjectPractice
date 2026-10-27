//
// Created by x3r1x on 10/20/26.
//

#ifndef SFML_TEST_MAPVIEW_H
#define SFML_TEST_MAPVIEW_H
#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "../../Entity/Map/TileType.h"
#include "../IDrawable.hpp"

class MapView: public IDrawable
{
    int m_height;
    int m_width;
    std::vector<TileType> m_grid;

    sf::Texture m_texture;
    sf::Sprite m_sprite;
public:
    MapView(int height, int width);

    void SetGrid(const std::vector<TileType> &grid);

    void Draw(sf::RenderWindow &window) override;
};

#endif // SFML_TEST_MAPVIEW_H
