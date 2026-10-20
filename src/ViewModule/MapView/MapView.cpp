//
// Created by x3r1x on 10/20/26.
//

#include "MapView.h"

#include <SFML/Graphics/RectangleShape.hpp>

#include "../../constants.cpp"

MapView::MapView()
{
    m_sprite = sf::RectangleShape(MAP_SIZE);
}

void MapView::SetPosition(const sf::Vector2f newPosition)
{
    m_sprite.setPosition(newPosition);
}

void MapView::Draw(sf::RenderWindow &window)
{
    window.draw(m_sprite);
}