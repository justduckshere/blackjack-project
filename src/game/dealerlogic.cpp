#include "playgame.h"


void PlayGame::playDealersRound(PlayGameWrapper* wrapper) {
    cout << "Dealers card is: "<< wrapper->callGetHand(dealer).front().getValue() << " of "<< wrapper->callGetHand(dealer).front().getSuit() << endl << endl;
    bool hasAce = wrapper->callCheckIfHandHasAce(wrapper->callGetHand(dealer));
    bool shouldDraw = wrapper->callDetermineIfDealerShouldDraw(wrapper, hasAce);
    if (shouldDraw == true) {
        wrapper->callAddCardToHand(dealer, currentDeck.getDeck().back());
        wrapper->callRemovePlayedCard(currentDeck);
    }
}

bool PlayGame::determineIfDealerShouldDraw(PlayGameWrapper* wrapper, bool hasAce){
    bool drawCard = false;
    if (hasAce == true) {
        if (wrapper->callGetTotalHand(wrapper, dealer->getHand(), 11) < 17) {
            drawCard = true;
        }
    }else {
        int dealersHandTotal = wrapper->callGetTotalHand(wrapper, dealer->getHand());
        if (dealersHandTotal < 17) {
            drawCard = true;
        }
    }
    return drawCard;
}

Player* PlayGame::getDealer(){
    return this->dealer;
}

void PlayGame::setDealer(Player* dealer) {
    this->dealer = dealer;
}