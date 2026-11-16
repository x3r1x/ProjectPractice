//
// Created by gleb.ryzhov on 11/11/26.
//

#include "Note.hpp"

#include <utility>

#include "../../Entity/Map/Map.hpp"
#include "../../Entity/Map/TileType.hpp"
#include "../../ViewModule/View/View.hpp"

Note::Note(const sf::Vector2i position, std::string text)
    : IInteractable(position), m_text(std::move(text))
{
}

void Note::Interact(InteractionContext &context)
{
    if (!CanInteract())
    {
        return;
    }

    m_isCollected = true;

    const sf::Vector2i position = GetPosition();
    context.map.SetTile(position.x, position.y, TileType::CollectedNote);

    context.noteText = m_text;
    context.isNoteOpen = true;
    context.view.SetNoteText(m_text);
    context.view.SetIsShowingNote(true);
}

bool Note::CanInteract() const
{
    return !m_isCollected;
}
