//
// Created by x3r1x on 10/20/26.
//

#ifndef SFML_TEST_VIEW_H
#define SFML_TEST_VIEW_H
#pragma once
#include <vector>

#include "../Camera/Camera.hpp"
#include "../Hud/Hud.hpp"
#include "../IDrawable.hpp"
#include "../MapView/MapView.hpp"

class Player;
class View
{
    sf::Font m_pauseFont;
    sf::Text m_pauseText;
    sf::Text m_continueText;
    sf::Text m_exitText;

    Hud m_hud;
    std::vector<IDrawable*> m_objects;
    sf::RenderWindow& m_window;

    Camera m_camera;

    static void HandleButtonHover(sf::Text& text, sf::Vector2f mousePosition);
    static void InitPauseText(sf::Text& text, const char *string, const sf::Vector2f offsetRatio);
public:
    View(sf::RenderWindow& window, MapView& map_view, Player& player);

    sf::RenderWindow& GetWindow() const;
    void SetMapPixelSize(sf::Vector2f size);
    void SetIsShowingNote(bool isShowingNote);
    void SetNoteText(const std::string& text);

    void DrawPauseMenu();
    bool IsExitClicked(const sf::Event& event) const;
    bool IsContinueClicked(const sf::Event& event) const;

    void DrawObjects();
    void UpdateCamera(sf::Vector2f playerPosition);
};

#endif // SFML_TEST_VIEW_H
