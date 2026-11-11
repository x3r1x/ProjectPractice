//
// Created by gleb.ryzhov on 11/11/26.
//

#ifndef SFML_TEST_KEY_HPP
#define SFML_TEST_KEY_HPP
#include "../IInteractable.h"

class Key: public IInteractable
{
    bool m_isCollected = false;
public:
    void Interact() override;
    bool CanInteract() override;
};

#endif // SFML_TEST_KEY_HPP
