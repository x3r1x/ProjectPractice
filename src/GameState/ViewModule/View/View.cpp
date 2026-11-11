//
// Created by x3r1x on 10/20/26.
//

#include "View.hpp"

#include <iostream>

#include "../../../AppConstants.hpp"
#include "../../Entity/Player/Player.hpp"
#include "../../GameConstants.hpp"
#include "../Hud/Hud.hpp"

constexpr auto FONT_PATH = "../assets/ttf/Jura-Bold.ttf";

View::View(sf::RenderWindow &window, MapView &map_view, Player &player)
    : m_pauseText(m_pauseFont), m_continueText(m_pauseFont), m_exitText(m_pauseFont),
      m_hud(player, window.getSize()), m_window(window),
      m_camera(window.getSize().x, window.getSize().y,
               sf::Vector2f(MAIN_ROOM_WIDTH * TILE_SIZE, MAIN_ROOM_HEIGHT * TILE_SIZE))
{
    if (!m_pauseFont.openFromFile(FONT_PATH))
    {
        std::cerr << "Error loading error font!" << std::endl;
        return;
    }

    m_objects.push_back(&map_view);
    m_objects.push_back(&player.GetView());

    InitPauseText(m_pauseText, PAUSE_TEXT, PAUSE_TEXT_OFFSET_RATIO);
    InitPauseText(m_continueText, CONTINUE_TEXT, CONTINUE_TEXT_OFFSET_RATIO);
    InitPauseText(m_exitText, EXIT_TEXT, EXIT_TEXT_OFFSET_RATIO);
}

void View::InitPauseText(sf::Text &text, const char *string, const sf::Vector2f offsetRatio) const
{
    text.setCharacterSize(PAUSE_TEXT_FONT_SIZE);
    text.setOutlineThickness(PAUSE_TEXT_OUTLINE_THICKNESS);
    text.setOutlineColor(PAUSE_TEXT_OUTLINE_COLOR);
    text.setString(string);
    const auto bounds = text.getLocalBounds();
    text.setOrigin(bounds.position + bounds.size / 2.0f);
    text.setPosition({m_window.getSize().x * offsetRatio.x, m_window.getSize().y * offsetRatio.y});
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

void View::HandleButtonHover(sf::Text &text, const sf::Vector2f mousePosition)
{
    const auto bounds = text.getGlobalBounds();
    const bool hovered = bounds.contains(mousePosition);

    if (hovered)
    {
        text.setFillColor(PAUSE_TEXT_HOVER_COLOR);
    }
    else
    {
        text.setFillColor(PAUSE_TEXT_FILL_COLOR);
    }
}

void View::DrawPauseMenu()
{
    sf::RectangleShape backgroundTint(sf::Vector2f(m_window.getSize()));
    backgroundTint.setFillColor(PAUSE_BACKGROUND_TINT_COLOR);

    const sf::Vector2f mousePos(sf::Mouse::getPosition(m_window));

    HandleButtonHover(m_exitText, mousePos);
    HandleButtonHover(m_continueText, mousePos);

    m_window.draw(backgroundTint);
    m_window.draw(m_pauseText);
    m_window.draw(m_continueText);
    m_window.draw(m_exitText);
}

bool View::IsExitClicked(const sf::Event &event) const
{
    const auto *click = event.getIf<sf::Event::MouseButtonPressed>();

    if (!click || click->button != sf::Mouse::Button::Left)
    {
        return false;
    }

    const auto position = m_window.mapPixelToCoords(click->position, m_window.getDefaultView());

    return m_exitText.getGlobalBounds().contains(position);
}

bool View::IsContinueClicked(const sf::Event &event) const
{
    const auto *click = event.getIf<sf::Event::MouseButtonPressed>();

    if (!click || click->button != sf::Mouse::Button::Left)
    {
        return false;
    }

    const auto position = m_window.mapPixelToCoords(click->position, m_window.getDefaultView());

    return m_continueText.getGlobalBounds().contains(position);
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
