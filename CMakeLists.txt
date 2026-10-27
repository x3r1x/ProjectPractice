cmake_minimum_required(VERSION 3.16)
project(sfml-test)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 3 COMPONENTS Graphics REQUIRED)

add_executable(app src/main.cpp
        src/Game/Game.cpp
        src/Game/Game.hpp
        src/Entity/Player/Player.cpp
        src/Entity/Player/Player.hpp
        src/Entity/Map/Map.cpp
        src/Entity/Map/Map.hpp
        src/constants.hpp
        src/ViewModule/View/View.cpp
        src/ViewModule/View/View.hpp
        src/ViewModule/IDrawable.hpp
        src/ViewModule/PlayerView/PlayerView.cpp
        src/ViewModule/PlayerView/PlayerView.hpp
        src/ViewModule/MapView/MapView.cpp
        src/ViewModule/MapView/MapView.hpp
        src/EventListener/EventListener.cpp
        src/EventListener/EventListener.hpp
        src/ViewModule/Hud/Hud.cpp
        src/ViewModule/Hud/Hud.hpp
        src/ViewModule/Camera/Camera.cpp
        src/ViewModule/Camera/Camera.hpp
        src/CollisionHandler/CollisionHandler.cpp
        src/CollisionHandler/CollisionHandler.hpp
        src/Entity/Map/TileType.h
)
target_link_libraries(app PRIVATE SFML::Graphics)