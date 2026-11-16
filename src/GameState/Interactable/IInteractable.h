//
// Created by gleb.ryzhov on 11/11/26.
//

#ifndef SFML_TEST_IINTERACTABLE_H
#define SFML_TEST_IINTERACTABLE_H
#pragma once

#include <string>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include "../GameConstants.hpp"

class View;
class Map;
class Player;

struct InteractionContext
{
    Player &player;
    Map &map;
    View &view;
    bool &isNoteOpen;
    std::string &noteText;
};

class IInteractable
{
    sf::Vector2i m_position;

public:
    explicit IInteractable(const sf::Vector2i position) : m_position(position) {}
    virtual ~IInteractable() = default;

    sf::Vector2i GetPosition() const
    {
        return m_position;
    }

    virtual sf::FloatRect GetBounds() const
    {
        return sf::FloatRect(
            {static_cast<float>(m_position.x * TILE_SIZE),
             static_cast<float>(m_position.y * TILE_SIZE)},
            {static_cast<float>(TILE_SIZE), static_cast<float>(TILE_SIZE)});
    }

    virtual sf::Vector2f GetPromptPosition() const
    {
        const sf::FloatRect bounds = GetBounds();
        return bounds.position + bounds.size / 2.0f;
    }

    virtual void Interact(InteractionContext &context) = 0;
    virtual bool CanInteract() const = 0;
};

#endif // SFML_TEST_IINTERACTABLE_H
