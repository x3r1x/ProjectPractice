//
// Created by x3r1x on 10/20/26.
//

#include "View.hpp"

#include "../../Entity/Player/Player.hpp"
#include "../../GameConstants.hpp"
#include "../../../AppConstants.hpp"
#include "../Hud/Hud.hpp"

View::View(sf::RenderWindow& window, MapView &map_view, Player &player)
    : m_hud(player), m_window(window), m_camera(WINDOW_WIDTH, WINDOW_HEIGHT,
               sf::Vector2f(MAIN_ROOM_WIDTH * TILE_SIZE, MAIN_ROOM_HEIGHT * TILE_SIZE))
{
    m_objects.push_back(&map_view);
    m_objects.push_back(&player.GetView());
}

sf::RenderWindow &View::GetWindow() const
{
    return m_window;
}

void View::SetMapPixelSize(const sf::Vector2f size)
{
    m_camera.SetMapPixelSize(size);
}

void View::SetNoteText(const std::string &text)
{
    m_hud.SetNoteText(text);
}

void View::SetIsShowingNote(const bool isShowingNote)
{
    m_hud.SetIsShowingNote(isShowingNote);
}

void View::DrawObjects()
{
    m_window.setView(m_camera.GetView());

    for (IDrawable *object : m_objects)
    {
        object->Draw(m_window);
    }

    m_window.setView(m_window.getDefaultView());
    m_hud.Draw(m_window);
}

void View::UpdateCamera(const sf::Vector2f playerPosition)
{
    m_camera.Follow(playerPosition);
}
