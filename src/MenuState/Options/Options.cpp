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

constexpr auto FONT_PATH = "../assets/ttf/Orbitron-Black.ttf";

Options::Options(sf::RenderWindow &window, std::function<void()> onBack)
    : m_titleText(m_font), m_backText(m_font), m_background(window.getSize()), m_window(window),
      m_onBack(std::move(onBack)), m_windowSize(window.getSize())
{
    if (!m_font.openFromFile(FONT_PATH))
    {
        std::cerr << "Failed to load menu page font!" << std::endl;
    }

    InitText(m_titleText, OPTIONS_TITLE_TEXT, OPTIONS_TITLE_OFFSET_RATIO);
    InitText(m_backText, OPTIONS_BACK_TEXT, OPTIONS_BACK_OFFSET_RATIO);
}

void Options::InitText(sf::Text &text, const std::string& string, const sf::Vector2f offsetRatio) const
{
    text.setString(string);
    text.setCharacterSize(MAIN_MENU_TEXT_FONT_SIZE);
    text.setOutlineThickness(MAIN_MENU_TEXT_OUTLINE_THICKNESS);
    text.setOutlineColor(MAIN_MENU_TEXT_OUTLINE_COLOR);
    text.setPosition({m_windowSize.x * offsetRatio.x,
                      m_windowSize.y * offsetRatio.y});
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

    sf::RectangleShape tint({static_cast<float>(m_windowSize.x), static_cast<float>(m_windowSize.y)});
    tint.setFillColor(OPTIONS_TINT_COLOR);
    m_window.draw(tint);
    m_window.draw(m_titleText);
    m_window.draw(m_backText);
}
