//
// Created by x3r1x on 11/3/26.
//

#include "./MainMenu.hpp"

#include <iostream>
#include <utility>

#include "../AppConstants.hpp"
#include "../utils.hpp"
#include "MainMenuConstants.hpp"

constexpr auto BACKGROUND_SPRITE_PATH = "../assets/png/MainScreen.png";
constexpr auto FONT_PATH = "../assets/ttf/Orbitron-Black.ttf";

MainMenu::MainMenu(sf::RenderWindow &window, std::function<void()> startGame)
    : m_text(m_font), m_backgroundSprite(m_texture), m_window(window), m_onStartGame(std::move(startGame))
{
    if (!m_texture.loadFromFile(BACKGROUND_SPRITE_PATH))
    {
        std::cerr << "Error loading background texture for main menu!" << std::endl;
        return;
    }

    m_backgroundFrameSize =
        sf::Vector2i({static_cast<int>(m_texture.getSize().x / BACKGROUND_COLUMNS),
                      static_cast<int>(m_texture.getSize().y / BACKGROUND_ROWS)});

    m_backgroundRow = GenerateRandomNumber(0, BACKGROUND_ROWS);
    m_backgroundColumn = GenerateRandomNumber(0, BACKGROUND_COLUMNS);
    SetSprite(m_backgroundRow, m_backgroundColumn);

    m_backgroundSprite.setColor(BACKGROUND_TINT);

    if (!m_font.openFromFile(FONT_PATH))
    {
        std::cerr << "Error reading main menu title font!" << std::endl;
        return;
    }

    m_text.setCharacterSize(MAIN_MENU_TEXT_FONT_SIZE);
    m_text.setFillColor(MAIN_MENU_TEXT_FILL_COLOR);
    m_text.setOutlineThickness(MAIN_MENU_TEXT_OUTLINE_THICKNESS);
    m_text.setOutlineColor(MAIN_MENU_TEXT_OUTLINE_COLOR);
    m_text.setString(MAIN_MENU_PLAY_TEXT);
    m_text.setPosition(MAIN_MENU_PLAY_OFFSET);
}

void MainMenu::DrawTitleText()
{
    m_text.setString(MAIN_MENU_TITLE_TEXT);
    m_text.setPosition(MAIN_MENU_TITLE_OFFSET);

    m_window.draw(m_text);
}

void MainMenu::DrawPlayText()
{
    m_text.setString(MAIN_MENU_PLAY_TEXT);
    m_text.setPosition(MAIN_MENU_PLAY_OFFSET);

    m_window.draw(m_text);
}

void MainMenu::SetSprite(const int row, const int column)
{

    m_backgroundSprite.setTextureRect(sf::IntRect(
        {column * m_backgroundFrameSize.x, row * m_backgroundFrameSize.y}, m_backgroundFrameSize));

    m_backgroundSprite.setScale({static_cast<float>(WINDOW_WIDTH) / m_backgroundFrameSize.x,
                                 static_cast<float>(WINDOW_HEIGHT) / m_backgroundFrameSize.y});
}

void MainMenu::HandleEvent(const sf::Event &event)
{
    if (const auto buttonPressed = event.getIf<sf::Event::MouseButtonPressed>())
    {
        if (buttonPressed->button == sf::Mouse::Button::Left)
        {
            const auto mousePosition = sf::Vector2f(buttonPressed->position);
            const auto textBounds = m_text.getGlobalBounds();

            if (textBounds.contains(mousePosition))
            {
                m_onStartGame();
            }
        }
    }
}

void MainMenu::Update(const float deltaTime)
{
    m_rowTimeRemaining -= deltaTime;
    m_columnTimeRemaining -= deltaTime;

    if (m_rowTimeRemaining < 0)
    {
        m_rowTimeRemaining = BACKGROUND_ROW_INTERVAL;
        m_backgroundRow = GenerateRandomNumber(0, BACKGROUND_ROWS);

        SetSprite(m_backgroundRow, m_backgroundColumn);
    }

    if (m_columnTimeRemaining < 0)
    {
        m_columnTimeRemaining = BACKGROUND_COLUMN_INTERVAL;
        m_backgroundColumn = GenerateRandomNumber(0, BACKGROUND_COLUMNS);

        SetSprite(m_backgroundRow, m_backgroundColumn);
    }
}

void MainMenu::Draw()
{
    m_window.draw(m_backgroundSprite);
    DrawTitleText();
    DrawPlayText();
}
