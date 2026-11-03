//
// Created by x3r1x on 11/3/26.
//

#ifndef SFML_TEST_INTERACCTIONDATA_HPP
#define SFML_TEST_INTERACCTIONDATA_HPP
#pragma once
#include <cstdint>
#include <string>

#include <SFML/System/Vector2.hpp>

#include "../Entity/Map/Room.hpp"

enum class InteractionType: uint8_t
{
    None = 0,
    Door = 1,
    Note = 2,
    Key = 3
};

typedef struct
{
    InteractionType type = InteractionType::None;

    std::string noteText;

    Room targetRoom;
    sf::Vector2f spawnPosition;
} InteractionData;

#endif // SFML_TEST_INTERACCTIONDATA_HPP
