#include "playgame.h"


vector<Player*> PlayGame::getPlayerList(){
    return playerList;
}

void PlayGame::playPlayersRound(PlayGameWrapper* wrapper) {
    for (int i =0; i < getPlayerList().size(); i++) {
        if (wrapper->callGetPlayerHasGoneBust(getPlayerList()[i])  == false) {
            int playerResponse;
            cout << "Would Player " << i + 1 << " like another card (1 = yes)" << endl;
            playerResponse = wrapper->getUserIntResponse();
            if (playerResponse == 1) {
                wrapper->callDealToPlayer(wrapper, i);
                cout << "\tPlayer " << i+1 << " has ";
                wrapper->callDisplayHand(getPlayerList()[i]);
                if (wrapper->callCheckIfHandHasGoneBust(wrapper, getPlayerList()[i]->getHand()) == true) {
                    getPlayerList()[i]->setPlayerHasGoneBust();
                    cout << "Sorry - you have gone bust!" << endl << endl;
                }
            }else {
                cout << "\tPlayer " << i+1 << " has ";
                wrapper->callDisplayHand(getPlayerList()[i]);
            }
            wrapper->callSetHighestValidHandValueForPlayer(wrapper, getPlayerList()[i], false);
        }
    }
}

void PlayGame::setPlayerList(vector<Player*> players){
    this->playerList = players;
}

void PlayGame::createPlayerList(PlayGameWrapper* wrapper){
    int playerCount =0;
    while (playerCount == 0) {
        cout << "How many players are playing blackjack? (please pick a number between 1 and 7)" <<endl;
        playerCount = wrapper->getUserIntResponse();
        if (playerCount >= 1 && playerCount <= 7) {
            break;
        }
        else {
            playerCount = 0;
        }
    }
    for (int i =0; i < playerCount; i++ ) {
        Player* player = new Player();
        playerList.push_back(player);
    }
    cout << "\t\tWe have " << getPlayerList().size() << " people playing Blackjack (plus a dealer)" <<endl <<endl;
}

