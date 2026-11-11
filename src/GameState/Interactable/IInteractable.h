//
// Created by gleb.ryzhov on 11/11/26.
//

#ifndef SFML_TEST_IINTERACTABLE_H
#define SFML_TEST_IINTERACTABLE_H
#pragma once

class IInteractable
{
    sf::Vector2i m_position;

public:
    explicit IInteractable(const sf::Vector2i position) : m_position(position) {}
    virtual ~IInteractable() = default;

    virtual void Interact() = 0;
    virtual bool CanInteract() = 0;
};

#endif // SFML_TEST_IINTERACTABLE_H
