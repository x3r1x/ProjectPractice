cmake_minimum_required(VERSION 3.16)
project(sfml-test)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 3 COMPONENTS Graphics REQUIRED)

add_executable(app src/main.cpp
        src/Game/Game.cpp
        src/Game/Game.h
        src/Player/Player.cpp
        src/Player/Player.h
        src/Map/Map.cpp
        src/Map/Map.h
        src/constants.cpp
        src/ViewModule/View/View.cpp
        src/ViewModule/View/View.h
        src/ViewModule/IDrawable.h
        src/ViewModule/PlayerView/PlayerView.cpp
        src/ViewModule/PlayerView/PlayerView.h
        src/ViewModule/MapView/MapView.cpp
        src/ViewModule/MapView/MapView.h)
target_link_libraries(app PRIVATE SFML::Graphics)