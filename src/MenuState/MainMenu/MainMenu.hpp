//
// Created by x3r1x on 11/3/26.
//

#ifndef SFML_TEST_MAINMENU_HPP
#define SFML_TEST_MAINMENU_HPP

#include <functional>
#include <vector>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "../../IState.hpp"
#include "../MainMenuConstants.hpp"
#include "../MenuBackground/MenuBackground.h"

class MainMenu: public IState
{
    sf::Font m_font;
    std::vector<sf::Text> m_texts;

    MenuBackground m_background;

    sf::RenderWindow& m_window;

    std::function<void()> m_onStartGame;
    std::function<void()> m_onExitApp;

    void InitText(const char* string, sf::Vector2f offsetRatio);
public:
    MainMenu(sf::RenderWindow& window, std::function<void()> startGame, std::function<void()> closeApp);

    void HandleEvent(const sf::Event &event) override;
    void Update(float deltaTime) override;
    void Draw() override;
};

#endif // SFML_TEST_MAINMENU_HPP
