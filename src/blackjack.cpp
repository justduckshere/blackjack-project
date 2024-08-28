#include <iostream>
#include "game/playgame.h"

using namespace std;

int main() {
    PlayGame playGame;
    PlayGameWrapper* playGameWrapper = new PlayGame();
    playGame.playGame(playGameWrapper);
}