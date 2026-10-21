//
// Created by x3r1x on 10/20/26.
//

#ifndef SFML_TEST_MAPVIEW_H
#define SFML_TEST_MAPVIEW_H
#pragma once
#include "../IDrawable.h"

class MapView: public IDrawable
{
public:
    MapView();

    void SetPosition(sf::Vector2f newPosition);
    void Draw(sf::RenderWindow &window) override;
};

#endif // SFML_TEST_MAPVIEW_H
