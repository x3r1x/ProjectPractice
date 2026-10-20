//
// Created by x3r1x on 10/20/26.
//

#ifndef SFML_TEST_IDRAWABLE_H
#define SFML_TEST_IDRAWABLE_H
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class IDrawable
{
protected:
    sf::RectangleShape m_sprite;

public:
    virtual ~IDrawable() = default;

    virtual void SetPosition(sf::Vector2f newPosition) = 0;
    virtual void Draw(sf::RenderWindow& window) = 0;
};

#endif // SFML_TEST_IDRAWABLE_H
