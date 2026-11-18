//
// Created by x3r1x on 10/20/26.
//

#ifndef SFML_TEST_MAP_H
#define SFML_TEST_MAP_H
#pragma once

#include "../Enemy/EnemyType.hpp"
#include "../../Interactable/IInteractable.h"
#include "../../ViewModule/MapView/MapView.hpp"
#include "Room.hpp"
#include "TileType.hpp"

class Map
{
    Room m_room = Room::Main;

    std::vector<TileType> m_grid;
    std::vector<std::unique_ptr<IInteractable>> m_interactableObjects;
    std::vector<EnemySpawnInfo> m_enemySpawns;

    int m_width{};
    int m_height{};

    MapView m_view;

    void ReadRoom(const char *structure);
    static TileType GetTileType(char tileAbbreviation);

    void ChangeToMainRoom();
    void ChangeToEnnardRoom();
    void ChangeToCircusBabyRoom();
    void ChangeToElectricalRoom();

public:
    Map();

    MapView &GetView();
    Room GetRoom() const;
    void SetInteraction(bool canInteract);
    void SetInteractingObject(const IInteractable &interactable);
    TileType GetTile(float worldX, float worldY) const;
    void SetTile(int worldX, int worldY, TileType type);
    const std::vector<EnemySpawnInfo> &GetEnemySpawns() const;

    void ChangeRoom(Room room);
    std::vector<sf::FloatRect> GetNearbyCollidableTiles(const sf::FloatRect &bounds) const;
    IInteractable *GetInteractableAt(const sf::FloatRect &bounds) const;
};

#endif // SFML_TEST_MAP_H
