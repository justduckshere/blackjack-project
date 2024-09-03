#include "playgame.h"

bool PlayGame::verifyHandHasWon(PlayGameWrapper* wrapper, vector<Card> hand){
    if (wrapper->callCheckIfHandHasAce(hand) == true) {
        if (wrapper->callCheckIfHandHasWonWithAce(wrapper, hand, 1) == true || wrapper->callCheckIfHandHasWonWithAce(wrapper, hand, 11) == true){
            return true;
        }
    } else {
        if (wrapper->callCheckIfHandHasWon(wrapper, hand) == true){
            return true;
        }
    }
    return false;
}

bool PlayGame::checkIfHandHasAce(vector<Card> hand){
    for (int i =0; i < hand.size(); i++) {
        if (hand[i].getValue() == "ace") {
            return true;
        }
    }
    return false;
}

bool PlayGame::checkIfHandHasWon(PlayGameWrapper *wrapper, vector<Card> hand, int aceValue){
    int count = 0; 
    bool oneAceFound = false;
    for (int i =0; i < hand.size(); i++){
        int cardValue = wrapper->callGetCardTrueValue(hand[i]);
        if (oneAceFound == true && hand[i].getValue() == "ace") {
            count +=1;
        } else if (hand[i].getValue() == "ace"){
            count += aceValue;
            oneAceFound = true;
        }else {
            count += cardValue;
        }
    }
    if (count == 21) {
        return true;
    }
    return false;
}

bool PlayGame::checkIfHandHasWon(PlayGameWrapper *wrapper, vector<Card> hand){
    int count = 0; 
    for (int i =0; i < hand.size(); i++){
        count += wrapper->callGetCardTrueValue(hand[i]);
    }
    if (count == 21) {
        return true;
    }
    return false;
}

vector<int> PlayGame::verifyAnyPlayerHasAchieved21(PlayGameWrapper *wrapper){
    vector<int> playersReached21;
    for(int i =0; i < getPlayerList().size(); i++) {
        if (wrapper->callVerifyHandHasWon(wrapper, getPlayerList()[i]->getHand()) == true){
            playersReached21.push_back(i);
        }
    }
    return playersReached21;
}

bool PlayGame::checkIfHandHasGoneBust(PlayGameWrapper *wrapper, vector<Card> hand){
    int count = 0;
    for (int i =0; i < hand.size(); i++){
        count += wrapper->callGetCardTrueValue(hand[i]);
    }

    if (count > 21) {
        return true;
    }
    return false;
}

bool PlayGame::checkIfAllPlayersHaveGoneBust(PlayGameWrapper *wrapper) {
    bool allPlayersAreBust = true;        
    for(int i =0; i < getPlayerList().size(); i++) {
        if (wrapper->callCheckIfHandHasGoneBust(wrapper, callGetHand(getPlayerList()[i])) == false){
            return false;
        }   
    }
    return true;
}


