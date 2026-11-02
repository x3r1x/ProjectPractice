//
// Created by x3r1x on 10/28/26.
//

#ifndef SFML_TEST_TILETYPR_H
#define SFML_TEST_TILETYPR_H

#pragma once
#include <cstdint>

enum class TileType : uint8_t
{
    Empty = 0,
    Solid = 1,
    Platform = 2,
    Note = 3,
    CollectedNote = 4,
    Key = 5,
    CollectedKey = 6,
    LeftDoorClosed = 7,
    RightDoorClosed = 8,
    LeftDoorOpen = 9,
    RightDoorOpen = 10
};

static bool IsInteractable(const TileType type)
{
    return type == TileType::Note || type == TileType::Key || type == TileType::LeftDoorClosed ||
           type == TileType::RightDoorClosed || type == TileType::LeftDoorOpen ||
           type == TileType::RightDoorOpen;
}

static bool IsBumpable(const TileType type)
{
    return type == TileType::Solid || type == TileType::Platform;
}

#endif // SFML_TEST_TILETYPR_H
