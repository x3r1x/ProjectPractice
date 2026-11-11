//
// Created by gleb.ryzhov on 11/11/26.
//

#ifndef SFML_TEST_NOTE_HPP
#define SFML_TEST_NOTE_HPP
#include <string>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "../IInteractable.h"

class Note: public IInteractable
{
    sf::Font m_font;
    sf::Text m_text;

    std::string m_string;

    bool m_isCollected = false;
public:
    Note();

    void Interact() override;
    bool CanInteract() override;
};

#endif // SFML_TEST_NOTE_HPP
