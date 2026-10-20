//
// Created by x3r1x on 10/20/26.
//

#ifndef SFML_TEST_MAP_H
#define SFML_TEST_MAP_H
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

#include "../ViewModule/MapView/MapView.h"

class Map
{
    sf::Vector2f m_bounds;
    sf::RectangleShape m_shape;

    MapView m_view;
public:
    Map();

    MapView& GetView();
};

#endif // SFML_TEST_MAP_H
