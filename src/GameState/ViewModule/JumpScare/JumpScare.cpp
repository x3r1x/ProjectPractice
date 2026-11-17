//
// Created by x3r1x on 11/16/26.
//

#include "JumpScare.hpp"

#include <iostream>

#include "../../GameConstants.hpp"

JumpScare::JumpScare(const std::string& texturePath, sf::Vector2u windowSize)
    : m_sprite(m_texture)
{
    if (!m_texture.loadFromFile(texturePath))
    {
        std::cout << "Error loading JumpScare texture: " << texturePath << std::endl;
        return;
    }
    m_sprite.setTexture(m_texture);

    m_sprite.setScale({static_cast<float>(windowSize.x) / JUMPSCARE_FRAME_SIZE.x,
                       static_cast<float>(windowSize.y) / JUMPSCARE_FRAME_SIZE.y});
}

void JumpScare::play() {
    m_currentFrame = 0;
    m_elapsedTime = 0.0f;
    m_isPlaying = true;

    m_sprite.setTextureRect(sf::IntRect({0, 0}, JUMPSCARE_FRAME_SIZE));
}

void JumpScare::update(const float dt) {
    if (!m_isPlaying) return;

    m_elapsedTime += dt;
    if (m_elapsedTime >= JUMPSCARE_FRAME_DURATION) {
        m_elapsedTime = 0;
        m_currentFrame++;

        if (m_currentFrame >= JUMPSCARE_FRAMES) {
            m_isPlaying = false;
            return;
        }

        int left = m_currentFrame % JUMPSCARE_FRAMES * JUMPSCARE_FRAME_SIZE.x;
        int top = m_currentFrame / JUMPSCARE_FRAMES * JUMPSCARE_FRAME_SIZE.y;
        m_sprite.setTextureRect(sf::IntRect({left, top}, JUMPSCARE_FRAME_SIZE));
    }
}

void JumpScare::render(sf::RenderWindow& window) const {
    if (!m_isPlaying) return;

    sf::View oldView = window.getView();
    window.setView(window.getDefaultView());
    window.draw(m_sprite);
    window.setView(oldView);
}

bool JumpScare::isPlaying() const
{
    return m_isPlaying;
}