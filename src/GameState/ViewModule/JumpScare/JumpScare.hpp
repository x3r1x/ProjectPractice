//
// Created by x3r1x on 11/16/26.
//

#ifndef SFML_TEST_JUMPSCARE_HPP
#define SFML_TEST_JUMPSCARE_HPP
#pragma once

#include <functional>
#include <string>

#include <SFML/Graphics.hpp>

class JumpScare {
    sf::Texture m_texture;
    sf::Sprite m_sprite;

    int m_currentFrame = 0;
    float m_elapsedTime = 0.0;
    bool m_isPlaying = false;

    std::function<void()> m_onEnd;
public:
    JumpScare(const std::string& texturePath, sf::Vector2u windowSize, std::function<void()> onEnd);

    void Play();
    void Update(float dt);
    void Draw(sf::RenderWindow& window) const;

    bool IsPlaying() const;
};

#endif // SFML_TEST_JUMPSCARE_HPP
