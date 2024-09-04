#include "playgame.h"

bool PlayGame::verifyHandis21(PlayGameWrapper* wrapper, vector<Card> hand){
    if (wrapper->callHandHasAce(hand) == true) {
        if (wrapper->callHandis21WithAce(wrapper, hand, 1) == true || wrapper->callHandis21WithAce(wrapper, hand, 11) == true){
            return true;
        }
    } else {
        if (wrapper->callHandis21(wrapper, hand) == true){
            return true;
        }
    }
    return false;
}

bool PlayGame::handHasAce(vector<Card> hand){
    for (int i =0; i < hand.size(); i++) {
        if (hand[i].getValue() == "ace") {
            return true;
        }
    }
    return false;
}

bool PlayGame::handis21(PlayGameWrapper *wrapper, vector<Card> hand, int aceValue){
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

bool PlayGame::handis21(PlayGameWrapper *wrapper, vector<Card> hand){
    int count = 0; 
    for (int i =0; i < hand.size(); i++){
        count += wrapper->callGetCardTrueValue(hand[i]);
    }
    if (count == 21) {
        return true;
    }
    return false;
}

bool PlayGame::handHasGoneBust(PlayGameWrapper *wrapper, vector<Card> hand){
    int count = 0;
    for (int i =0; i < hand.size(); i++){
        count += wrapper->callGetCardTrueValue(hand[i]);
    }

    if (count > 21) {
        return true;
    }
    return false;
}

bool PlayGame::allPlayersHaveGoneBust(PlayGameWrapper *wrapper) {
    bool allPlayersAreBust = true;        
    for(int i =0; i < getPlayerList().size(); i++) {
        if (wrapper->callHandHasGoneBust(wrapper, wrapper->callGetHand(getPlayerList()[i])) == false){
            return false;
        }   
    }
    return true;
}


vector<int> PlayGame::returnListOfPlayersAt21(PlayGameWrapper *wrapper){
    vector<int> playersReached21;
    for(int i =0; i < getPlayerList().size(); i++) {
        if (wrapper->callVerifyHandis21(wrapper, getPlayerList()[i]->getHand()) == true){
            playersReached21.push_back(i);
        }
    }
    return playersReached21;
}

