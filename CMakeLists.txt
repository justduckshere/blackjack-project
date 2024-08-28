cmake_minimum_required(VERSION 3.20)
project(blackjack-project)

enable_testing()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)

add_subdirectory(tests)


set(SOURCES
    src/blackjack.cpp
    src/hand/deck.cpp 
    src/hand/card.cpp
    src/player/player.cpp
    src/game/gamelogic.cpp
    src/game/dealerlogic.cpp
    src/game/playerlogic.cpp
    src/game/handmanagement.cpp
    src/game/winnerhandler.cpp
    src/game/playgame.cpp
    src/game/wrapper.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})