//
// Created by x3r1x on 11/3/26.
//

#include "./MainMenu.hpp"

#include <iostream>

#include "../AppConstants.hpp"
#include "../utils.hpp"
#include "MainMenuConstants.hpp"

constexpr auto BACKGROUND_SPRITE_PATH = "../assets/png/MainScreen.png";

MainMenu::MainMenu(sf::RenderWindow &window) : m_backgroundSprite(m_texture), m_window(window)
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
}

void MainMenu::SetSprite(const int row, const int column)
{

    m_backgroundSprite.setTextureRect(sf::IntRect(
        {column * m_backgroundFrameSize.x, row * m_backgroundFrameSize.y}, m_backgroundFrameSize));

    m_backgroundSprite.setScale({static_cast<float>(WINDOW_WIDTH) / m_backgroundFrameSize.x,
                                 static_cast<float>(WINDOW_HEIGHT) / m_backgroundFrameSize.y});
}

void MainMenu::HandleEvent(const sf::Event &event) {}

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
}