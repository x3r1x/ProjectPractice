//
// Created by x3r1x on 10/20/26.
//

#ifndef SFML_TEST_MAPVIEW_H
#define SFML_TEST_MAPVIEW_H
#pragma once
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "../../Entity/Map/TileType.hpp"
#include "../IDrawable.hpp"

class MapView: public IDrawable
{
    int m_height{};
    int m_width{};
    std::vector<TileType> m_grid;

    sf::Texture m_texture;
    sf::Sprite m_sprite;

    sf::Font m_font;
    sf::Text m_text;

    bool m_canInteract = false;
public:
    MapView();

    void SetSize(int width, int height);
    void SetCanInteract(bool canInteract);
    void SetInteractionPosition(sf::FloatRect tileRect, TileType type);
    void SetGrid(const std::vector<TileType> &grid);

    void Draw(sf::RenderWindow &window) override;
};

#endif // SFML_TEST_MAPVIEW_H
