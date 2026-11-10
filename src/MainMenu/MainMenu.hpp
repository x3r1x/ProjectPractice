//
// Created by x3r1x on 11/3/26.
//

#ifndef SFML_TEST_MAINMENU_HPP
#define SFML_TEST_MAINMENU_HPP

#include <functional>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "../IState.hpp"
#include "MainMenuConstants.hpp"

class MainMenu: public IState
{
    sf::Font m_font;
    sf::Text m_text;

    sf::Vector2i m_backgroundFrameSize;
    sf::Texture m_texture;
    sf::Sprite m_backgroundSprite;
    float m_rowTimeRemaining = BACKGROUND_ROW_INTERVAL;
    float m_columnTimeRemaining = BACKGROUND_COLUMN_INTERVAL;


    int m_backgroundRow{};
    int m_backgroundColumn{};

    sf::RenderWindow& m_window;

    std::function<void()> m_onStartGame;
    void SetSprite(int row, int column);
    void DrawTitleText();
    void DrawPlayText();
public:
    MainMenu(sf::RenderWindow& window, std::function<void()> startGame);

    void HandleEvent(const sf::Event &event) override;
    void Update(float deltaTime) override;
    void Draw() override;
};

#endif // SFML_TEST_MAINMENU_HPP
