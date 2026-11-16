//
// Created by gleb.ryzhov on 11/11/26.
//

#ifndef SFML_TEST_KEY_HPP
#define SFML_TEST_KEY_HPP
#pragma once

#include "../IInteractable.h"

class Key : public IInteractable
{
    bool m_isCollected = false;

public:
    explicit Key(sf::Vector2i position);

    void Interact(InteractionContext &context) override;
    bool CanInteract() const override;
};

#endif // SFML_TEST_KEY_HPP