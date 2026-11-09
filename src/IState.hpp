//
// Created by x3r1x on 11/10/26.
//

#ifndef SFML_TEST_ISTATE_HPP
#define SFML_TEST_ISTATE_HPP

#include <SFML/Window/Event.hpp>

class IState
{
public:
    virtual ~IState() = default;

    virtual void HandleEvent(const sf::Event &event) = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Draw() = 0;
};

#endif // SFML_TEST_ISTATE_HPP
