//
// Created by gleb.ryzhov on 11/11/26.
//

#ifndef SFML_TEST_DOOR_HPP
#define SFML_TEST_DOOR_HPP
#include <SFML/System/Vector2.hpp>

#include "../../Entity/Map/Room.hpp"
#include "../IInteractable.h"

class Door: public IInteractable
{
    Room m_targetRoom;
    sf::Vector2f m_spawnPosition;

    bool m_isClosed = false;
public:
    Door(Room targetRoom, sf::Vector2f spawnPosition);

    void Interact() override;
    bool CanInteract() override;
};

#endif // SFML_TEST_DOOR_HPP