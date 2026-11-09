//
// Created by x3r1x on 10/21/26.
//

#include "Hud.hpp"

#include <iostream>

#include "../../Entity/Player/Player.hpp"
#include "../../GameConstants.hpp"
#include "../../../AppConstants.hpp"

constexpr auto FONT_PATH = "../assets/ttf/Euclid Circular B Bold.ttf";

Hud::Hud(const Player &player) : m_player(player)
{
    m_staminaBackground.setSize(HUD_STAMINA_SIZE);
    m_staminaBackground.setPosition({20, 20});
    m_staminaBackground.setFillColor(HUD_STAMINA_BACKGROUND_COLOR);

    m_staminaFill.setPosition({20, 20});
    m_staminaFill.setFillColor(HUD_STAMINA_FILL);

    if (!m_noteFont.openFromFile("../assets/ttf/Euclid Circular B Bold.ttf"))
    {
        std::cerr << "Error reading font!" << std::endl;
    }

    m_noteBackground.setSize({
        static_cast<float>(WINDOW_WIDTH) * NOTE_BACKGROUND_WIDTH_MULTIPLIER,
        static_cast<float>(WINDOW_HEIGHT) * NOTE_BACKGROUND_HEIGHT_MULTIPLIER
    });

    m_noteBackground.setFillColor(NOTE_BACKGROUND_COLOR);
    m_noteBackground.setPosition({
        static_cast<float>(WINDOW_WIDTH) * NOTE_SCREEN_WIDTH,
        static_cast<float>(WINDOW_HEIGHT) * NOTE_SCREEN_HEIGHT
    });

    m_noteText.setCharacterSize(NOTE_TEXT_SIZE);
    m_noteText.setFillColor(NOTE_TEXT_FILL_COLOR);

    const auto bounds = m_noteText.getLocalBounds();

    m_noteText.setPosition({
        WINDOW_WIDTH * NOTE_SCREEN_WIDTH + NOTE_TEXT_OFFSET_X,
        WINDOW_HEIGHT * NOTE_SCREEN_HEIGHT + NOTE_TEXT_OFFSET_Y
    });
}

void Hud::SetNoteText(const std::string &text)
{
    m_noteText.setString(text);
}

void Hud::SetIsShowingNote(const bool isShowingNote)
{
    m_isShowingNote = isShowingNote;
}

void Hud::Draw(sf::RenderWindow &window)
{
    const float hudLeftRatio = m_player.GetStamina() / PLAYER_MAX_STAMINA;
    m_staminaFill.setSize({HUD_WIDTH * hudLeftRatio, HUD_HEIGHT});

    window.draw(m_staminaBackground);
    window.draw(m_staminaFill);

    if (m_isShowingNote)
    {
        window.draw(m_noteBackground);
        window.draw(m_noteText);
    }
}