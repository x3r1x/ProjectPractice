//
// Created by x3r1x on 10/20/26.
//

#ifndef SFML_TEST_MAP_H
#define SFML_TEST_MAP_H
#pragma once

#include "../../ViewModule/MapView/MapView.hpp"
#include "TileType.hpp"

class Map
{
    std::vector<TileType> m_grid;
    int m_width;
    int m_height;

    MapView m_view;

    static TileType GetTileType(char tileAbbreviation);
public:
    Map();

    MapView& GetView();
    void SetInteraction(bool canInteract);
    void SetInteractingTile(sf::FloatRect tileRect);
    TileType GetTile(float worldX, float worldY) const;
    void SetTile(int worldX, int worldY, TileType type);

    std::vector<sf::FloatRect> GetNearbyCollidableTiles(const sf::FloatRect& bounds) const;
    std::vector<sf::FloatRect> GetNearbyInteractableTiles(const sf::FloatRect& bounds) const;
};

#endif // SFML_TEST_MAP_H
