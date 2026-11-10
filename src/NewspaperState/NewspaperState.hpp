//
// Created by x3r1x on 11/3/26.
//

#pragma once

#include <filesystem>
#include <functional>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "../IState.hpp"

class NewspaperState : public IState
{
    sf::RenderWindow &m_window;
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    std::function<void()> m_onContinue;

public:
    NewspaperState(sf::RenderWindow &window, const std::string& imagePath,
                   std::function<void()> onContinue);

    void HandleEvent(const sf::Event &event) override;
    void Update(float deltaTime) override;
    void Draw() override;
};
