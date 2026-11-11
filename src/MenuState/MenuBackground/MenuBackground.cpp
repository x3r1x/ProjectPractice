//
// Created by gleb.ryzhov on 11/11/26.
//

#include "MenuBackground.hpp"

#include <stdexcept>

#include "../../AppConstants.hpp"
#include "../../utils.hpp"

constexpr auto BACKGROUND_SPRITE_PATH = "../assets/png/MainScreen.png";

MenuBackground::MenuBackground(const sf::Vector2u windowSize) : m_sprite(m_texture), m_windowSize(windowSize)
{
    if (!m_texture.loadFromFile(BACKGROUND_SPRITE_PATH))
    {
        throw std::runtime_error("Failed to load menu background texture");
    }

    m_frameSize = {static_cast<int>(m_texture.getSize().x / BACKGROUND_COLUMNS),
                   static_cast<int>(m_texture.getSize().y / BACKGROUND_ROWS)};
    m_row = GenerateRandomNumber(0, BACKGROUND_ROWS);
    m_column = GenerateRandomNumber(0, BACKGROUND_COLUMNS);
    SetSprite();

    m_sprite.setColor(BACKGROUND_TINT);

    m_sprite.setScale({static_cast<float>(m_windowSize.x) / m_frameSize.x,
                       static_cast<float>(m_windowSize.y) / m_frameSize.y});
}

void MenuBackground::SetSprite()
{
    m_sprite.setTextureRect(
        sf::IntRect({m_column * m_frameSize.x, m_row * m_frameSize.y}, m_frameSize));
}

void MenuBackground::Update(const float deltaTime)
{
    m_rowTimeRemaining -= deltaTime;
    m_columnTimeRemaining -= deltaTime;

    if (m_rowTimeRemaining < 0)
    {


        if (m_row != 0)
        {
            m_row = 0;
            m_rowTimeRemaining = BACKGROUND_ROW_DEFAULT_INTERVAL;
        }
        else
        {
            m_row = GenerateRandomNumber(0, BACKGROUND_ROWS);
            m_rowTimeRemaining = BACKGROUND_ROW_SCARE_INTERVAL;
        }

        SetSprite();
    }

    if (m_columnTimeRemaining < 0)
    {
        m_columnTimeRemaining = BACKGROUND_COLUMN_INTERVAL;
        m_column = GenerateRandomNumber(0, BACKGROUND_COLUMNS);
        SetSprite();
    }
}

void MenuBackground::Draw(sf::RenderWindow &window) const
{
    window.setView(window.getDefaultView());
    window.draw(m_sprite);
}
