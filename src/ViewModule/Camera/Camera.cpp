//
// Created by x3r1x on 10/21/26.
//

#include "Camera.hpp"

#include <algorithm>

Camera::Camera(float width, float height, const sf::Vector2f mapPixelSize)
{
    m_view = sf::View(sf::FloatRect({0.0, 0.0}, {width, height}));
    m_mapPixelSize = mapPixelSize;
}

sf::View &Camera::GetView()
{
    return m_view;
}

void Camera::Follow(const sf::Vector2f position)
{
    const float minX = m_view.getSize().x / 2;
    float maxX = m_mapPixelSize.x - (m_view.getSize().x / 2);
    const float minY = m_view.getSize().y / 2.0f;
    float maxY = m_mapPixelSize.y - (m_view.getSize().y / 2.0f);

    if (maxX < minX) maxX = minX;
    if (maxY < minY) maxY = minY;

    float clampedX = std::clamp(position.x, minX, maxX);
    float clampedY = std::clamp(position.y, minY, maxY);

    m_view.setCenter({clampedX, clampedY});
}
