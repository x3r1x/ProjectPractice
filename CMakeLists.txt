cmake_minimum_required(VERSION 3.16)
project(sfml-test)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 3 COMPONENTS Graphics REQUIRED)

add_executable(app src/main.cpp
        src/GameState/Game/Game.cpp
        src/GameState/Game/Game.hpp
        src/GameState/Entity/Player/Player.cpp
        src/GameState/Entity/Player/Player.hpp
        src/GameState/Entity/Map/Map.cpp
        src/GameState/Entity/Map/Map.hpp
        src/GameState/GameConstants.hpp
        src/GameState/ViewModule/View/View.cpp
        src/GameState/ViewModule/View/View.hpp
        src/GameState/ViewModule/IDrawable.hpp
        src/GameState/ViewModule/PlayerView/PlayerView.cpp
        src/GameState/ViewModule/PlayerView/PlayerView.hpp
        src/GameState/ViewModule/MapView/MapView.cpp
        src/GameState/ViewModule/MapView/MapView.hpp
        src/GameState/EventListener/EventListener.cpp
        src/GameState/EventListener/EventListener.hpp
        src/GameState/ViewModule/Hud/Hud.cpp
        src/GameState/ViewModule/Hud/Hud.hpp
        src/GameState/ViewModule/Camera/Camera.cpp
        src/GameState/ViewModule/Camera/Camera.hpp
        src/GameState/CollisionHandler/CollisionHandler.cpp
        src/GameState/CollisionHandler/CollisionHandler.hpp
        src/GameState/Entity/Map/TileType.hpp
        src/GameState/CollisionHandler/CollisionType.hpp
        src/GameState/Entity/Map/Room.hpp
        src/GameState/CollisionHandler/InteracctionData.hpp
        src/StateManager/StateManager.cpp
        src/StateManager/StateManager.hpp
        src/MenuState/MainMenu/MainMenu.cpp
        src/MenuState/MainMenu/MainMenu.hpp
        src/MenuState/Options/Options.cpp
        src/MenuState/Options/Options.hpp
        src/MenuState/Options/OptionsConstants.hpp
        src/MenuState/Tutorial/Tutorial.cpp
        src/MenuState/Tutorial/Tutorial.hpp
        src/MenuState/Tutorial/TutorialConstants.hpp
        src/AppConstants.hpp
        src/IState.hpp
        src/MenuState/MainMenuConstants.hpp
        src/utils.hpp
        src/MenuState/MenuBackground/MenuBackground.cpp
        src/MenuState/MenuBackground/MenuBackground.h
        src/NewspaperState/NewspaperState.cpp
        src/NewspaperState/NewspaperState.hpp
)
target_link_libraries(app PRIVATE SFML::Graphics)
