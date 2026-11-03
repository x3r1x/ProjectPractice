//
// Created by x3r1x on 10/20/26.
//

#ifndef SFML_TEST_MAP_H
#define SFML_TEST_MAP_H
#pragma once

#include "../../CollisionHandler/InteracctionData.hpp"
#include "../../ViewModule/MapView/MapView.hpp"
#include "Room.hpp"
#include "TileType.hpp"

class Map
{
    Room m_room = Room::Main;

    std::vector<TileType> m_grid;
    std::unordered_map<int, InteractionData> m_interactionData;

    int m_width{};
    int m_height{};

    MapView m_view;

    int GetTileIndex(int x, int y) const;

    const char *GetRoomStructure(Room room);
    void ReadRoom(const char *structure);
    static TileType GetTileType(char tileAbbreviation);

    void ChangeToMainRoom();
    void ChangeToEnnardRoom();
    void ChangeToCircusBabyRoom();
    void ChangeToElectricalRoom();

  public:
    Map();

    MapView &GetView();
    void SetInteraction(bool canInteract);
    void SetInteractingTile(sf::FloatRect tileRect);
    TileType GetTile(float worldX, float worldY) const;
    void SetTile(int worldX, int worldY, TileType type);
    void SetInteractionData(int x, int y, const InteractionData &data);
    const InteractionData *GetInteractionData(int x, int y) const;

    void ChangeRoom(Room room);
    std::vector<sf::FloatRect> GetNearbyCollidableTiles(const sf::FloatRect &bounds) const;
    std::vector<sf::FloatRect> GetNearbyInteractableTiles(const sf::FloatRect &bounds) const;
};

#endif // SFML_TEST_MAP_H
