//
// Created by x3r1x on 11/17/26.
//

#include "EnemyFactory.hpp"

#include <utility>

#include "../Enemies/Enemies.hpp"

std::unique_ptr<Enemy> EnemyFactory::Create(const EnemyType type,
                                            const sf::Vector2f spawnPosition,
                                            const sf::IntRect zoneTiles,
                                            std::function<void()> onJumpScareEnd,
                                            const sf::Vector2u windowSize)
{
    switch (type)
    {
    case EnemyType::FuntimeFreddy:
        return std::make_unique<FuntimeFreddy>(spawnPosition, zoneTiles, std::move(onJumpScareEnd),
                                               windowSize);
    case EnemyType::BonBon:
        return std::make_unique<BonBon>(spawnPosition, zoneTiles, std::move(onJumpScareEnd),
                                        windowSize);
    case EnemyType::Balora:
        return std::make_unique<Balora>(spawnPosition, zoneTiles, std::move(onJumpScareEnd),
                                        windowSize);
    case EnemyType::ElecroBab:
        return std::make_unique<ElecroBab>(spawnPosition, zoneTiles, std::move(onJumpScareEnd),
                                           windowSize);
    case EnemyType::BidyBab:
        return std::make_unique<BidyBab>(spawnPosition, zoneTiles, std::move(onJumpScareEnd),
                                         windowSize);
    case EnemyType::FuntimeFoxy:
        return std::make_unique<FuntimeFoxy>(spawnPosition, zoneTiles, std::move(onJumpScareEnd),
                                             windowSize);
    case EnemyType::CircusBaby:
        return std::make_unique<CircusBaby>(spawnPosition, zoneTiles, std::move(onJumpScareEnd),
                                            windowSize);
    default:
        return nullptr;
    }
}