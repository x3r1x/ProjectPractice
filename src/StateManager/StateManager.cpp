//
// Created by x3r1x on 11/3/26.
//

#include "./StateManager.hpp"

#include "../AppConstants.hpp"

StateManager::StateManager()
    : m_window(sf::RenderWindow(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), APP_NAME)),
      m_mainMenu(m_window, [this] { StartGame(); }, [this]{m_window.close();}), m_game(m_window), m_stateObject(&m_mainMenu)
{
    m_window.setKeyRepeatEnabled(false);
    m_state = AppState::MainMenu;
}

AppState StateManager::GetState() const
{
    return m_state;
}

void StateManager::Draw()
{
    m_window.clear();

    m_stateObject->Draw();

    m_window.display();
}

void StateManager::HandleEvents(const sf::Event &event)
{
    const auto* key = event.getIf<sf::Event::KeyPressed>();

    if (key && key->code == sf::Keyboard::Key::Escape)
    {
        if (m_state == AppState::GamePlaying)
        {
            m_state = AppState::GamePaused;
            return;
        }

        if (m_state == AppState::GamePaused)
        {
            m_state = AppState::GamePlaying;
            return;
        }
    }

    if (m_state != AppState::GamePaused)
    {
        m_stateObject->HandleEvent(event);
    }
}

void StateManager::Update(const float elapsedTime) const
{
    if (m_state == AppState::GamePaused)
    {
        return;
    }

    m_stateObject->Update(elapsedTime);
}

void StateManager::StartGame()
{
    m_state = AppState::GamePlaying;
    m_stateObject = &m_game;
}

void StateManager::Run()
{
    sf::Clock clock;

    while (m_window.isOpen())
    {
        while (const auto event = m_window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                m_window.close();
                break;
            }

            HandleEvents(*event);
        }

        const float elapsedTime = clock.restart().asSeconds();

        Update(elapsedTime);

        Draw();
    }
}
