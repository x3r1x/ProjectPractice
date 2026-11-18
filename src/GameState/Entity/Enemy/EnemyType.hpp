//
// Created by x3r1x on 11/17/26.
//

#ifndef SFML_TEST_ENEMYTYPE_HPP
#define SFML_TEST_ENEMYTYPE_HPP
#pragma once

#include <cstdint>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

enum class EnemyType : uint8_t
{
    FuntimeFreddy = 0,
    BonBon = 1,
    Balora = 2,
    ElecroBab = 3,
    BidyBab = 4,
    FuntimeFoxy = 5,
    CircusBaby
};

struct EnemyContext
{
    sf::Vector2f playerPosition;
    sf::Vector2f playerVelocity;
};

struct EnemySpawnInfo
{
    EnemyType type;
    sf::Vector2i spawnTile;
    sf::IntRect zoneTiles;
};

#endif // SFML_TEST_ENEMYTYPE_HPP
