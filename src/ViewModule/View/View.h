//
// Created by x3r1x on 10/20/26.
//

#ifndef SFML_TEST_VIEW_H
#define SFML_TEST_VIEW_H
#include <vector>

#include "../IDrawable.h"
#include "../MapView/MapView.h"
#include "../PlayerView/PlayerView.h"

class View
{
    std::vector<IDrawable*> m_objects;
    sf::RenderWindow m_window;

public:
    View(MapView& map_view, PlayerView& playerView);

    sf::RenderWindow& GetWindow();

    void DrawObjects();
};

#endif // SFML_TEST_VIEW_H
