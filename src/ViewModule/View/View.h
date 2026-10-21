//
// Created by x3r1x on 10/20/26.
//

#ifndef SFML_TEST_VIEW_H
#define SFML_TEST_VIEW_H
#pragma once
#include <vector>

#include "../../Hud/Hud.h"
#include "../Camera/Camera.h"
#include "../IDrawable.h"
#include "../MapView/MapView.h"

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
