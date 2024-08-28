add_library(blackjack 
blackjack.cpp 
hand/deck.cpp 
hand/card.cpp
player/player.cpp
game/gamelogic.cpp
game/dealerlogic.cpp
game/playerlogic.cpp
game/handmanagement.cpp
game/winnerhandler.cpp
game/playgame.cpp
game/wrapper.cpp
)
target_include_directories(blackjack PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} hand player playgame)