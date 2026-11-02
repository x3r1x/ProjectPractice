//
// Created by x3r1x on 11/2/26.
//

#ifndef SFML_TEST_COLLISIONTYPE_H
#define SFML_TEST_COLLISIONTYPE_H
#pragma once
#include <cstdint>

#include "../Entity/Map/TileType.hpp"

enum class CollisionType: uint8_t
{
    None = 0,
    Interaction = 1,
    Bump = 2
};

static CollisionType GetCollisionType(const TileType type)
{
    if (IsInteractable(type))
    {
        return CollisionType::Interaction;
    }

    if (IsBumpable(type))
    {
        return CollisionType::Bump;
    }

    return CollisionType::None;
}

#endif // SFML_TEST_COLLISIONTYPE_H
