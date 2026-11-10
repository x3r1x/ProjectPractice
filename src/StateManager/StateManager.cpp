//
// Created by x3r1x on 11/3/26.
//

#include "./StateManager.hpp"

#include "../AppConstants.hpp"
#include "../MenuState/Options/Options.hpp"
#include "../MenuState/Tutorial/Tutorial.hpp"
#include "../NewspaperState/NewspaperState.hpp"

constexpr auto GAME_START_SPRITE_PATH = "../assets/png/GameStart.jpg";
constexpr auto BAD_ENDING_SPRITE_PATH = "../assets/png/BadEnding.jpg";

StateManager::StateManager()
    : m_window(sf::RenderWindow(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), APP_NAME))
{
    m_window.setKeyRepeatEnabled(false);
    GoToMenu();
    ApplyStateChange();
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
    const auto *key = event.getIf<sf::Event::KeyPressed>();

    if (key && key->code == sf::Keyboard::Key::Escape)
    {
        if (m_state == AppState::GamePlaying || m_state == AppState::GamePaused)
        {
            SetGamePaused(m_state == AppState::GamePlaying);
            return;
        }
    }

    m_stateObject->HandleEvent(event);
    ApplyStateChange();
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
    m_pendingState = AppState::GamePlaying;
}

void StateManager::GoToMenu()
{
    m_pendingState = AppState::MainMenu;
}

void StateManager::ApplyStateChange()
{
    if (!m_pendingState)
    {
        return;
    }

    switch (*m_pendingState)
    {
    case AppState::MainMenu:
        m_stateObject = std::make_unique<MainMenu>(
            m_window, [this] { m_pendingState = AppState::Newspaper; },
            [this] { m_pendingState = AppState::Options; },
            [this] { m_pendingState = AppState::Tutorial; }, [this] { m_window.close(); });
        break;
    case AppState::Options:
        m_stateObject = std::make_unique<Options>(m_window, [this] { GoToMenu(); });
        break;
    case AppState::Tutorial:
        m_stateObject = std::make_unique<Tutorial>(m_window, [this] { GoToMenu(); });
        break;
    case AppState::Newspaper:
        m_stateObject = std::make_unique<NewspaperState>(m_window, GAME_START_SPRITE_PATH,
                                                         [this] { StartGame(); });
        break;
    case AppState::BadEnding:
        m_stateObject = std::make_unique<NewspaperState>(m_window, BAD_ENDING_SPRITE_PATH,
                                                         [this] { GoToMenu(); });
        break;
    case AppState::GamePlaying:
        m_stateObject = std::make_unique<Game>(
            m_window, [this] { SetGamePaused(false); }, [this] { GoToMenu(); },
            [this] { m_pendingState = AppState::BadEnding; });
        break;
    default:
        return;
    }

    m_state = *m_pendingState;
    m_pendingState.reset();
    m_window.setView(m_window.getDefaultView());
}

void StateManager::SetGamePaused(const bool paused)
{
    if (m_state != AppState::GamePlaying && m_state != AppState::GamePaused)
    {
        return;
    }

    dynamic_cast<Game &>(*m_stateObject).SetAppPause(paused);
    m_state = paused ? AppState::GamePaused : AppState::GamePlaying;
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
