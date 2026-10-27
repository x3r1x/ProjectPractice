//
// Created by x3r1x on 10/21/26.
//

#ifndef SFML_TEST_CAMERA_H
#define SFML_TEST_CAMERA_H
#pragma once
#include <SFML/Graphics/View.hpp>

class Camera
{
    sf::Vector2f m_mapPixelSize;
    sf::View m_view;

public:
    Camera(float width, float height, sf::Vector2f mapPixelSize);

    sf::View& GetView();

    void Follow(sf::Vector2f position);
};

#endif // SFML_TEST_CAMERA_H
