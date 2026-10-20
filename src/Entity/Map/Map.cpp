//
// Created by x3r1x on 10/20/26.
//

#include "Map.h"
#include "../../constants.cpp"

Map::Map()
{
    m_bounds = sf::Vector2f(MAP_SIZE);
    m_shape = sf::RectangleShape(m_bounds);

    m_shape.setPosition(sf::Vector2f(0,0));
}

MapView &Map::GetView()
{
    return m_view;
}