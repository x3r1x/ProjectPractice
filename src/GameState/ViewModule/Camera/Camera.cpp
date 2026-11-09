//
// Created by x3r1x on 10/21/26.
//

#include "Camera.hpp"

#include <algorithm>

#include "../../GameConstants.hpp"

Camera::Camera(float width, float height, const sf::Vector2f mapPixelSize)
{
    m_view = sf::View(sf::FloatRect({0, 0}, {width, height}));
    m_mapPixelSize = mapPixelSize;
    m_view.zoom(GAME_CAMERA_ZOOM);
}

void Camera::SetMapPixelSize(const sf::Vector2f size)
{
    m_mapPixelSize = size;
}

sf::View &Camera::GetView()
{
    return m_view;
}

void Camera::Follow(const sf::Vector2f position)
{
    const float halfWidth = m_view.getSize().x / 2;
    const float halfHeight = m_view.getSize().y / 2;

    const float minX = halfWidth;
    const float minY = halfHeight;

    const float maxX = m_mapPixelSize.x - halfWidth;
    const float maxY = m_mapPixelSize.y - halfHeight;

    const float clampedX = maxX < minX ? m_mapPixelSize.x / 2 : std::clamp(position.x, minX, maxX);

    const float clampedY = maxY < minY ? m_mapPixelSize.y / 2 : std::clamp(position.y, minY, maxY);

    m_view.setCenter({clampedX, clampedY});
}
