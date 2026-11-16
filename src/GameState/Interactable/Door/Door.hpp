//
// Created by gleb.ryzhov on 11/11/26.
//

#ifndef SFML_TEST_DOOR_HPP
#define SFML_TEST_DOOR_HPP
#pragma once

#include <SFML/System/Vector2.hpp>

#include "../../Entity/Map/Room.hpp"
#include "../IInteractable.h"

class Door : public IInteractable
{
    Room m_targetRoom;
    sf::Vector2f m_spawnPosition;
    bool m_isClosed = true;

    static sf::Vector2f GetRoomPixelSize(Room room);

public:
    Door(sf::Vector2i position, Room targetRoom, sf::Vector2f spawnPosition, bool isClosed = true);

    sf::FloatRect GetBounds() const override;
    void Interact(InteractionContext &context) override;
    bool CanInteract() const override;
};

#endif // SFML_TEST_DOOR_HPP
