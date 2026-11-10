//
// Created by x3r1x on 11/3/26.
//

#include "./MainMenu.hpp"

#include <iostream>
#include <utility>

#include "../../AppConstants.hpp"
#include "../MainMenuConstants.hpp"

constexpr auto FONT_PATH = "../assets/ttf/Orbitron-Black.ttf";

MainMenu::MainMenu(sf::RenderWindow &window, std::function<void()> startGame, std::function<void()> closeApp)
    : m_window(window), m_onStartGame(std::move(startGame)), m_onExitApp(std::move(closeApp))
{
    if (!m_font.openFromFile(FONT_PATH))
    {
        std::cerr << "Error reading main menu title font!" << std::endl;
        return;
    }

    InitText(MAIN_MENU_TITLE_TEXT, MAIN_MENU_TITLE_OFFSET_RATIO);
    InitText(MAIN_MENU_PLAY_TEXT, MAIN_MENU_PLAY_OFFSET_RATIO);
    InitText(MAIN_MENU_OPTIONS_TEXT, MAIN_MENU_OPTIONS_OFFSET_RATIO);
    InitText(MAIN_MENU_HTP_TEXT, MAIN_MENU_HTP_OFFSET_RATIO);
    InitText(MAIN_MENU_EXIT_TEXT, MAIN_MENU_EXIT_OFFSET_RATIO);
}

void MainMenu::InitText(const char *string, const sf::Vector2f offsetRatio)
{
    auto &text = m_texts.emplace_back(m_font);

    text.setCharacterSize(MAIN_MENU_TEXT_FONT_SIZE);
    text.setOutlineThickness(MAIN_MENU_TEXT_OUTLINE_THICKNESS);
    text.setOutlineColor(MAIN_MENU_TEXT_OUTLINE_COLOR);
    text.setString(string);
    text.setPosition({WINDOW_WIDTH * offsetRatio.x, WINDOW_HEIGHT * offsetRatio.y});
}

void MainMenu::HandleEvent(const sf::Event &event)
{
    if (const auto buttonPressed = event.getIf<sf::Event::MouseButtonPressed>())
    {
        if (buttonPressed->button == sf::Mouse::Button::Left && !m_texts.empty())
        {
            const auto mousePosition = sf::Vector2f(buttonPressed->position);
            const auto playTextBounds = m_texts[MAIN_MENU_PLAY_TEXT_INDEX].getGlobalBounds();

            if (playTextBounds.contains(mousePosition))
            {
                m_onStartGame();
                return;
            }

            const auto exitTextBounds = m_texts[MAIN_MENU_EXIT_TEXT_INDEX].getGlobalBounds();
            if (exitTextBounds.contains(mousePosition))
            {
                m_onExitApp();
                return;
            }
        }
    }

    const sf::Vector2f mousePos(sf::Mouse::getPosition(m_window));

    for (auto& m_text : m_texts)
    {
        if (m_text.getPosition() == sf::Vector2f(WINDOW_WIDTH * MAIN_MENU_TITLE_OFFSET_RATIO.x,
                                                 WINDOW_HEIGHT * MAIN_MENU_TITLE_OFFSET_RATIO.y))
        {
            continue;
        }

        const auto bounds = m_text.getGlobalBounds();
        const bool hovered = bounds.contains(mousePos);

        if (hovered)
        {
            m_text.setFillColor(MAIN_MENU_TEXT_HOVER_COLOR);
        }
        else
        {
            m_text.setFillColor(MAIN_MENU_TEXT_FILL_COLOR);
        }
    }
}

void MainMenu::Update(const float deltaTime)
{
    m_background.Update(deltaTime);
}

void MainMenu::Draw()
{
    m_background.Draw(m_window);
    for (const auto &text : m_texts)
    {
        m_window.draw(text);
    }
}
