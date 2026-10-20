//
// Created by x3r1x on 10/21/26.
//

#ifndef SFML_TEST_HUD_H
#define SFML_TEST_HUD_H
#include "../IDrawable.h"

class Player;
class Hud: public IDrawable
{
    const Player& m_player;
    sf::RectangleShape m_staminaBackground;
    sf::RectangleShape m_staminaFill;

public:
    explicit Hud(const Player& player);

    void Draw(sf::RenderWindow &window) override;
};

#endif // SFML_TEST_HUD_H
