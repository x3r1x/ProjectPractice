//
// Created by x3r1x on 9/23/26.
//

#include <SFML/Graphics.hpp>
#include <optional>

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Рыжов");
    sf::Color color = sf::Color::Green;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
                window.close();
            }


            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
            {
                color = sf::Color::Cyan;
            }
        }

        window.clear(color);
        window.display();
    }

    return 0;
}