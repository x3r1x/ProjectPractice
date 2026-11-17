//
// Created by x3r1x on 11/17/26.
//

#ifndef SFML_TEST_ENEMYFACTORY_HPP
#define SFML_TEST_ENEMYFACTORY_HPP
#pragma once

#include <memory>
#include <SFML/System/Vector2.hpp>

#include "../Enemy/Enemy.hpp"
#include "../EnemyType.hpp"

class EnemyFactory
{
public:
    static std::unique_ptr<Enemy> Create(EnemyType type, sf::Vector2f spawnPosition,
                                         sf::Vector2u windowSize);
};

#endif // SFML_TEST_ENEMYFACTORY_HPP
