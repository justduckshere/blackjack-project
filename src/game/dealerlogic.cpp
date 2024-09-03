#include "playgame.h"


void PlayGame::playDealersRound(PlayGameWrapper* wrapper) {
    cout << "Dealers card is: "<< wrapper->callGetHand(dealer).front().getValue() << " of "<< wrapper->callGetHand(dealer).front().getSuit() << endl << endl;
    bool hasAce = wrapper->callCheckIfHandHasAce(wrapper->callGetHand(dealer));
    bool shouldDraw = wrapper->callDetermineIfDealerShouldDraw(wrapper, hasAce);
    if (shouldDraw == true) {
        wrapper->callAddCardToHand(dealer, wrapper->callGetDeck(currentDeck).back());
        wrapper->callRemovePlayedCard(currentDeck);
    }
}

bool PlayGame::determineIfDealerShouldDraw(PlayGameWrapper* wrapper, bool hasAce){
    int dealersHandTotal = 0;
    if (hasAce == true) {
        // we only need to call the total for the instance of the ace = 11 as we need to treat the ace
        // as 11 to verify if it is over 17 
        dealersHandTotal = wrapper->callGetTotalHand(wrapper, wrapper->callGetHand(dealer), 11); 
    }else {
        dealersHandTotal = wrapper->callGetTotalHand(wrapper, wrapper->callGetHand(dealer));
    }
    if (dealersHandTotal < 17) {
        return true;
    }
    return false;
}

Player* PlayGame::getDealer(){
    return this->dealer;
}

void PlayGame::setDealer(Player* dealer) {
    this->dealer = dealer;
}