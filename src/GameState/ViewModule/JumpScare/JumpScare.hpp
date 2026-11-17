//
// Created by x3r1x on 11/16/26.
//

#ifndef SFML_TEST_JUMPSCARE_HPP
#define SFML_TEST_JUMPSCARE_HPP
#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class JumpScare {
    sf::Texture m_texture;
    sf::Sprite m_sprite;

    int m_currentFrame = 0;
    float m_elapsedTime = 0.0;
    bool m_isPlaying = false;

public:
    JumpScare(const std::string& texturePath, sf::Vector2u windowSize);

    void play();
    void update(float dt);
    void render(sf::RenderWindow& window) const;

    bool isPlaying() const;
};

#endif // SFML_TEST_JUMPSCARE_HPP
