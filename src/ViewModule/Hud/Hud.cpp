//
// Created by x3r1x on 10/21/26.
//

#include "Hud.hpp"

#include "../../Entity/Player/Player.hpp"
#include "../../constants.hpp"

Hud::Hud(const Player &player): m_player(player)
{
    m_staminaBackground.setSize(HUD_STAMINA_SIZE);
    m_staminaBackground.setPosition({20, 20});
    m_staminaBackground.setFillColor(HUD_STAMINA_BACKGROUND_COLOR);

    m_staminaFill.setPosition({20, 20});
    m_staminaFill.setFillColor(HUD_STAMINA_FILL);
}

void Hud::Draw(sf::RenderWindow &window)
{
    const float hudLeftRatio = m_player.GetStamina() / PLAYER_MAX_STAMINA;
    m_staminaFill.setSize({HUD_WIDTH * hudLeftRatio, HUD_HEIGHT});

    window.draw(m_staminaBackground);
    window.draw(m_staminaFill);
}