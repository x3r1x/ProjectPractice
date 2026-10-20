//
// Created by x3r1x on 10/20/26.
//

#include "View.h"
#include "../../constants.cpp"

View::View(MapView& map_view, PlayerView& playerView)
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

    for (IDrawable* object: m_objects)
    {
        object->Draw(m_window);
    }

    m_window.display();
}