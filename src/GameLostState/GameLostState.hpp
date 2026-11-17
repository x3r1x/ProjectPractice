//
// Created by gleb.ryzhov on 11/17/26.
//

#ifndef SFML_TEST_GAMELOSTSTATE_HPP
#define SFML_TEST_GAMELOSTSTATE_HPP
#include <functional>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "../IState.hpp"

class GameLostState: public IState
{
    sf::Texture m_deathScreenTexture;
    sf::Texture m_youDiedScreenTexture;

    sf::Sprite m_deathScreenSprite;
    sf::Sprite m_youDiedScreenSprite;

    sf::Font m_font;
    sf::Text m_text;

    sf::RenderWindow& m_window;

    std::function<void()> m_onExit;

    float m_screenDuration = 0;
    bool m_isYouDied = false;
public:
    GameLostState(sf::RenderWindow& window, std::function<void()> exit);

    void HandleEvent(const sf::Event &event) override;
    void Update(float deltaTime) override;
    void Draw() override;
};

#endif // SFML_TEST_GAMELOSTSTATE_HPP
