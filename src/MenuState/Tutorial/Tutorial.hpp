//
// Created by x3r1x on 11/3/26.
//

#pragma once

#include <functional>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "../../IState.hpp"
#include "../MenuBackground/MenuBackground.hpp"

class Tutorial: public IState
{
    sf::Font m_font;
    sf::Text m_titleText;
    sf::Text m_bodyText;
    sf::Text m_backText;

    MenuBackground m_background;
    sf::RenderWindow &m_window;
    std::function<void()> m_onBack;

    sf::Vector2u m_windowSize;
    void InitBigText(sf::Text &text, const std::string& string, sf::Vector2f offsetRatio) const;
public:
    Tutorial(sf::RenderWindow &window, std::function<void()> onBack);

    void HandleEvent(const sf::Event &event) override;
    void Update(float deltaTime) override;
    void Draw() override;
};
