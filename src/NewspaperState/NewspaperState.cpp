//
// Created by x3r1x on 11/3/26.
//

#include "NewspaperState.hpp"

#include <algorithm>
#include <stdexcept>
#include <utility>

NewspaperState::NewspaperState(sf::RenderWindow &window, const std::string& imagePath,
                               std::function<void()> onContinue)
    : m_window(window), m_sprite(m_texture), m_onContinue(std::move(onContinue))
{
    if (!m_texture.loadFromFile(imagePath))
    {
        throw std::runtime_error("Failed to load newspaper!");
    }

    m_texture.setSmooth(true);
    m_sprite.setTextureRect(sf::IntRect({0, 0}, sf::Vector2i(m_texture.getSize())));
}

void NewspaperState::HandleEvent(const sf::Event &event)
{
    const auto *key = event.getIf<sf::Event::KeyPressed>();
    const auto *mouse = event.getIf<sf::Event::MouseButtonPressed>();

    if ((key && (key->code == sf::Keyboard::Key::Enter || key->code == sf::Keyboard::Key::Space)) ||
        (mouse && mouse->button == sf::Mouse::Button::Left))
    {
        m_onContinue();
    }
}

void NewspaperState::Update(float) {}

void NewspaperState::Draw()
{
    m_window.setView(m_window.getDefaultView());

    const auto viewSize = m_window.getView().getSize();
    const auto imageSize = sf::Vector2f(m_texture.getSize());
    const float scale = std::min(viewSize.x / imageSize.x, viewSize.y / imageSize.y);

    m_sprite.setScale({scale, scale});
    m_sprite.setPosition((viewSize - imageSize * scale) / 2.f);
    m_window.draw(m_sprite);
}
