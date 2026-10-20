//
// Created by x3r1x on 10/20/26.
//

#ifndef SFML_TEST_PLAYERVIEW_H
#define SFML_TEST_PLAYERVIEW_H
#include "../IDrawable.h"

class PlayerView: public IDrawable
{
public:
    PlayerView();

    void SetPosition(sf::Vector2f newPosition);
    void Draw(sf::RenderWindow &window) override;
};

#endif // SFML_TEST_PLAYERVIEW_H
