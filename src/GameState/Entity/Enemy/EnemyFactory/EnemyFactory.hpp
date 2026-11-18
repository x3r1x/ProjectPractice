//
// Created by x3r1x on 11/17/26.
//

#ifndef SFML_TEST_ENEMYFACTORY_HPP
#define SFML_TEST_ENEMYFACTORY_HPP
#pragma once

#include <functional>
#include <memory>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include "../Enemy/Enemy.hpp"
#include "../EnemyType.hpp"

class EnemyFactory
{
public:
    static std::unique_ptr<Enemy> Create(EnemyType type, sf::Vector2f spawnPosition,
                                         sf::IntRect zoneTiles,
                                         std::function<void()> onJumpScareEnd,
                                         sf::Vector2u windowSize);
};

#endif // SFML_TEST_ENEMYFACTORY_HPP
