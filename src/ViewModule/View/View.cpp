//
// Created by x3r1x on 10/20/26.
//

#include "View.h"

#include "../../constants.cpp"
#include "../../Hud/Hud.h"

View::View(MapView& map_view, PlayerView& playerView, Hud& hud)
    : m_hud(hud), m_camera(WINDOW_WIDTH, WINDOW_HEIGHT)
{
    m_window = sf::RenderWindow(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "NaB: SL");

    m_objects.push_back(&map_view);
    m_objects.push_back(&playerView);
}

sf::RenderWindow &View::GetWindow()
{
    return m_window;
}

void View::DrawObjects()
{
    m_window.clear();

    m_window.setView(m_camera.GetView());

    for (IDrawable* object: m_objects)
    {
        object->Draw(m_window);
    }

    m_window.setView(m_window.getDefaultView());
    m_hud.Draw(m_window);

    m_window.display();
}

void View::UpdateCamera(const sf::Vector2f playerPosition)
{
    m_camera.Follow(playerPosition);
}