//
// Created by x3r1x on 10/20/26.
//

#ifndef SFML_TEST_MAP_H
#define SFML_TEST_MAP_H
#pragma once

#include "../../ViewModule/MapView/MapView.hpp"
#include "TileType.h"

class Map
{
    std::vector<TileType> m_grid;
    int m_width;
    int m_height;

    MapView m_view;
public:
    Map();

    MapView& GetView();

    TileType GetTile(float worldX, float worldY) const;
    void SetTile(int worldX, int worldY, TileType type);
    bool IsSolid(float worldX, float worldY);
};

#endif // SFML_TEST_MAP_H
