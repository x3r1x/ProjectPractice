//
// Created by x3r1x on 10/20/26.
//

#ifndef SFML_TEST_VIEW_H
#define SFML_TEST_VIEW_H
#pragma once
#include <vector>

#include "../Camera/Camera.hpp"
#include "../Hud/Hud.hpp"
#include "../IDrawable.hpp"
#include "../MapView/MapView.hpp"

class Player;
class View
{
    Hud m_hud;
    std::vector<IDrawable*> m_objects;
    sf::RenderWindow m_window;

    Camera m_camera;

public:
    View(MapView& map_view, Player& player);

    sf::RenderWindow& GetWindow();

    void DrawObjects();
    void UpdateCamera(sf::Vector2f playerPosition);
};

#endif // SFML_TEST_VIEW_H
