//
// Created by gleb.ryzhov on 11/17/26.
//

#include "GameLostState.hpp"

#include <iostream>
#include <utility>

#include "GameLostConstants.hpp"

constexpr auto DEATH_SCREEN_PATH = "../assets/png/Death Screen.png";
constexpr auto YOU_DIED_SCREEN_PATH = "../assets/png/YouDiedScreen.png";
constexpr auto FONT_PATH = "../assets/ttf/Jura-Bold.ttf";

GameLostState::GameLostState(sf::RenderWindow &window, std::function<void()> exit)
    : m_deathScreenSprite(m_deathScreenTexture), m_youDiedScreenSprite(m_youDiedScreenTexture),
      m_text(m_font), m_window(window), m_onExit(std::move(exit))
{
    if (!m_deathScreenTexture.loadFromFile(DEATH_SCREEN_PATH) ||
        !m_youDiedScreenTexture.loadFromFile(YOU_DIED_SCREEN_PATH) ||
        !m_font.openFromFile(FONT_PATH))
    {
        std::cerr << "Error loading GameLostState config!" << std::endl;
        return;
    }

    m_deathScreenSprite.setTexture(m_deathScreenTexture, true);
    m_youDiedScreenSprite.setTexture(m_youDiedScreenTexture, true);

    m_text.setCharacterSize(GAME_LOST_TEXT_FONT_SIZE);
    m_text.setOutlineThickness(GAME_LOST_TEXT_OUTLINE_THICKNESS);
    m_text.setOutlineColor(GAME_LOST_TEXT_OUTLINE_COLOR);
    m_text.setString(GAME_LOST_TEXT);
    m_text.setPosition({m_window.getSize().x * GAME_LOST_TEXT_OFFSET_RATIO.x,
                        m_window.getSize().y * GAME_LOST_TEXT_OFFSET_RATIO.y});

    const auto bound = m_text.getLocalBounds();
    m_text.setOrigin({bound.size.x / 2, bound.size.y / 2});

    m_deathScreenSprite.setScale(
        {static_cast<float>(m_window.getSize().x) / GAME_LOST_DEATH_FRAME_SIZE.x,
         static_cast<float>(m_window.getSize().y) / GAME_LOST_DEATH_FRAME_SIZE.y});

    m_youDiedScreenSprite.setScale(
        {static_cast<float>(m_window.getSize().x) / m_youDiedScreenTexture.getSize().x,
         static_cast<float>(m_window.getSize().y) / m_youDiedScreenTexture.getSize().y});

    if (m_music.openFromFile("../assets/ost/Game Over Theme.mp3")) {
        m_music.setLooping(true);
        m_music.setVolume(50.f);
        m_music.play();
    }
}

void GameLostState::HandleEvent(const sf::Event &event)
{
    if (const auto buttonPressed = event.getIf<sf::Event::MouseButtonPressed>())
    {
        if (m_isYouDied && buttonPressed->button == sf::Mouse::Button::Left)
        {
            const auto mousePosition = m_window.mapPixelToCoords(buttonPressed->position);
            const auto textBounds = m_text.getGlobalBounds();

            if (textBounds.contains(mousePosition))
            {
                m_onExit();
                return;
            }
        }
    }

    const sf::Vector2f mousePos(sf::Mouse::getPosition(m_window));
    const auto bounds = m_text.getGlobalBounds();
    const bool hovered = bounds.contains(mousePos);

    if (hovered && m_isYouDied)
    {
        m_text.setFillColor(GAME_LOST_TEXT_HOVER_COLOR);
    }
    else
    {
        m_text.setFillColor(GAME_LOST_TEXT_FILL_COLOR);
    }
}

void GameLostState::Update(const float deltaTime)
{
    m_screenDuration += deltaTime;

    if (m_screenDuration > GAME_LOST_DEATH_SCREEN_DURATION)
    {
        m_isYouDied = true;
    }

    if (!m_isYouDied)
    {
        constexpr int frameWidth = static_cast<int>(GAME_LOST_DEATH_FRAME_SIZE.x);
        const int totalFrames = static_cast<int>(m_deathScreenTexture.getSize().x) / frameWidth;

        const int rawFrame = static_cast<int>(m_screenDuration / GAME_LOST_FRAME_DURATION);
        const int currentFrame = rawFrame % totalFrames;

        m_deathScreenSprite.setTextureRect(
            sf::IntRect({currentFrame * frameWidth, 0}, sf::Vector2i(GAME_LOST_DEATH_FRAME_SIZE)));
    }

    const int deathScreenTransparency =
        m_screenDuration < GAME_LOST_DEATH_SCREEN_DURATION
            ? static_cast<std::uint8_t>(255.f *
                                        (GAME_LOST_DEATH_SCREEN_DURATION - m_screenDuration) /
                                        GAME_LOST_DEATH_SCREEN_DURATION)
            : 0;

    m_deathScreenSprite.setColor(sf::Color(255, 255, 255, deathScreenTransparency));
}

void GameLostState::Draw()
{
    m_window.draw(m_youDiedScreenSprite);

    m_window.draw(m_text);

    m_window.draw(m_deathScreenSprite);
}