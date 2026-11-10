//
// Created by x3r1x on 11/3/26.
//

#include "Options.hpp"

#include <iostream>
#include <stdexcept>
#include <utility>

#include <SFML/Graphics/RectangleShape.hpp>

#include "../../AppConstants.hpp"
#include "../MainMenuConstants.hpp"
#include "OptionsConstants.hpp"

constexpr auto FONT_PATH = "../assets/ttf/Orbitron-Black.ttf";

Options::Options(sf::RenderWindow &window, std::function<void()> onBack)
    : m_titleText(m_font), m_backText(m_font), m_window(window), m_onBack(std::move(onBack))
{
    if (!m_font.openFromFile(FONT_PATH))
    {
        std::cerr << "Failed to load menu page font!" << std::endl;
    }

    m_titleText.setString(OPTIONS_TITLE_TEXT);
    m_titleText.setCharacterSize(MAIN_MENU_TEXT_FONT_SIZE);
    m_titleText.setOutlineThickness(MAIN_MENU_TEXT_OUTLINE_THICKNESS);
    m_titleText.setOutlineColor(MAIN_MENU_TEXT_OUTLINE_COLOR);
    m_titleText.setPosition({WINDOW_WIDTH * OPTIONS_TITLE_OFFSET_RATIO.x,
                             WINDOW_HEIGHT * OPTIONS_TITLE_OFFSET_RATIO.y});

    m_backText.setString(OPTIONS_BACK_TEXT);
    m_backText.setCharacterSize(MAIN_MENU_TEXT_FONT_SIZE);
    m_backText.setFillColor(MAIN_MENU_TEXT_FILL_COLOR);
    m_backText.setOutlineThickness(MAIN_MENU_TEXT_OUTLINE_THICKNESS);
    m_backText.setOutlineColor(MAIN_MENU_TEXT_OUTLINE_COLOR);
    m_backText.setPosition(
        {WINDOW_WIDTH * OPTIONS_BACK_OFFSET_RATIO.x, WINDOW_HEIGHT * OPTIONS_BACK_OFFSET_RATIO.y});
}

void Options::HandleEvent(const sf::Event &event)
{
    if (const auto *key = event.getIf<sf::Event::KeyPressed>();
        key && key->code == sf::Keyboard::Key::Escape)
    {
        m_onBack();
        return;
    }

    if (const auto *mouse = event.getIf<sf::Event::MouseButtonPressed>();
        mouse && mouse->button == sf::Mouse::Button::Left &&
        m_backText.getGlobalBounds().contains(m_window.mapPixelToCoords(mouse->position)))
    {
        m_onBack();
    }
}

void Options::Update(const float deltaTime)
{
    m_background.Update(deltaTime);

    const auto mousePosition = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
    const bool hovered = m_backText.getGlobalBounds().contains(mousePosition);
    m_backText.setFillColor(hovered ? MAIN_MENU_TEXT_HOVER_COLOR : MAIN_MENU_TEXT_FILL_COLOR);
}

void Options::Draw()
{
    m_background.Draw(m_window);

    sf::RectangleShape tint({static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT)});
    tint.setFillColor(OPTIONS_TINT_COLOR);
    m_window.draw(tint);
    m_window.draw(m_titleText);
    m_window.draw(m_backText);
}
