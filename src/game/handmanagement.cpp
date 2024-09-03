#include "playgame.h"



void PlayGame::dealToEveryone(PlayGameWrapper *wrapper){
    for (int i =0; i < getPlayerList().size(); i++) {    
        wrapper->callDealToPlayer(wrapper, i);
    }
    wrapper->callAddCardToHand(dealer, wrapper->callGetDeck(currentDeck).back());
    wrapper->callRemovePlayedCard(currentDeck);
}

void PlayGame::dealToPlayer(PlayGameWrapper *wrapper, int playerNumber) {
    wrapper->callAddCardToHand(getPlayerList()[playerNumber], wrapper->callGetDeck(currentDeck).back());
    cout << "\t\tPlayer " << playerNumber+1 << " has been dealt a " << wrapper->callGetHand(getPlayerList()[playerNumber]).front().getValue() << " of "<< wrapper->callGetHand(getPlayerList()[playerNumber]).front().getSuit() << endl<<endl;
    wrapper->callRemovePlayedCard(currentDeck);
}

int PlayGame::getUserIntResponse() {
    int response;
    cin >> response;
    return response;
}

Deck PlayGame::getDeck(){
    return this->currentDeck;
}

int PlayGame::getTotalHand(PlayGameWrapper *wrapper, vector<Card> hand){
    int count = 0;
    for (int i =0; i <hand.size(); i++) {
        count += wrapper->callGetCardTrueValue(hand[i]);
    }
    return count;
}

int PlayGame::getTotalHand(PlayGameWrapper *wrapper, vector<Card> hand, int aceValue){
    int count = 0;
    bool aceFound = false;
    for (int i =0; i < hand.size(); i++) {
        if (hand[i].getValue() == "ace" && aceValue == 11 && aceFound == false) {
            count += 11;
            aceFound = true;
        } else {
            count += wrapper->callGetCardTrueValue(hand[i]);
        }
    }
    return count;
}

void PlayGame::setCurrentDeck(Deck inputDeck){
    currentDeck = inputDeck;
}


