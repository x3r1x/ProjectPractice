//
// Created by x3r1x on 10/21/26.
//

#include "Camera.hpp"

Camera::Camera(float width, float height)
{
    m_view = sf::View(sf::FloatRect({0.0, 0.0}, {width, height}));
}

sf::View &Camera::GetView()
{
    return m_view;
}

void Camera::Follow(const sf::Vector2f position)
{
    m_view.setCenter(position);
}
