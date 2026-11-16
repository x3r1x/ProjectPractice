//
// Created by gleb.ryzhov on 11/11/26.
//

#ifndef SFML_TEST_NOTE_HPP
#define SFML_TEST_NOTE_HPP
#pragma once

#include <string>

#include "../IInteractable.h"

class Note : public IInteractable
{
    std::string m_text;
    bool m_isCollected = false;

public:
    Note(sf::Vector2i position, std::string text);

    void Interact(InteractionContext &context) override;
    bool CanInteract() const override;
};

#endif // SFML_TEST_NOTE_HPP
