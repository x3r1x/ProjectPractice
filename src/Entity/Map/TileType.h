//
// Created by x3r1x on 10/28/26.
//

#ifndef SFML_TEST_TILETYPR_H
#define SFML_TEST_TILETYPR_H

#pragma once
#include <cstdint>

enum class TileType : uint8_t {
    Empty = 0,
    Solid = 1,
    Platform = 2,
    Note = 3,
    Key = 4,
    LeftDoorClosed = 5,
    RightDoorClosed = 6,
    LeftDoorOpen = 7,
    RightDoorOpen = 8
};

#endif // SFML_TEST_TILETYPR_H
