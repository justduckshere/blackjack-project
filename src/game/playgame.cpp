#include "playgame.h"


vector<Player*> PlayGame::playerList;
Deck PlayGame::currentDeck;
Player* PlayGame::dealer;

void PlayGame::playGame(PlayGameWrapper *wrapper){
    wrapper->callInitialiseGame(wrapper);
    bool winner = false;
    vector<int> playersWhoHaveWon = wrapper->callReturnListOfPlayersAt21(wrapper);
    wrapper->callSetHighestValidHandValueForPlayer(wrapper, wrapper->callGetDealer(), true); 
    bool dealerHasWon = wrapper->callVerifyHandis21(wrapper, wrapper->callGetHand(wrapper->callGetDealer()));
    if (dealerHasWon == true || playersWhoHaveWon.size() != 0) {
        cout << "Dealers second card is: "<< wrapper->callGetHand(wrapper->callGetDealer()).front().getValue() << " of "<< wrapper->callGetHand(wrapper->callGetDealer()).front().getSuit() << endl << endl;
        wrapper->callDisplayWin(dealerHasWon, playersWhoHaveWon, 21);
    }else {
        while (winner == false) {
            cout << "Next round has started" << endl << endl;
            winner = wrapper->callRegularGamePlay(wrapper); 
        }
    }
}


void PlayGame::initialiseGame(PlayGameWrapper* wrapper) {
    currentDeck = Deck();
    wrapper->callInit(currentDeck);
    dealer = new Player();
    wrapper->callShuffle(currentDeck);
    wrapper->callCreatePlayerList(wrapper);
    wrapper->callDealToEveryone(wrapper);
    cout << "\tThe Dealer has a " << wrapper->callGetHand(dealer).front().getValue() << " of "<< wrapper->callGetHand(dealer).front().getSuit() << endl<<endl;
    wrapper->callDealToEveryone(wrapper);
    cout << "\t\tThe Dealer has placed their second card face-down." << endl<<endl;
}

bool PlayGame::regularGamePlay(PlayGameWrapper *wrapper){
    playPlayersRound(wrapper);
    cout << "\tDealer has ";
    wrapper->callDisplayHand(dealer);
    wrapper->callSetHighestValidHandValueForPlayer(wrapper, dealer, true);

    if (wrapper->callGetCurrentTotal(dealer) > 21) {
        cout << "Dealer has gone bust! Everyone else has won!!" << endl <<endl;
        return true;
    }else if (wrapper->callAllPlayersHaveGoneBust(wrapper) == true) {
        cout << "All players but the dealer have gone bust. Game over." << endl<<endl;
        return true;
    } else if (wrapper->callReturnListOfPlayersAt21(wrapper).size() != 0) {
        bool dealerHasWon = wrapper->callVerifyHandis21(wrapper, wrapper->callGetHand(getDealer()));
        vector<int> playersWhoHaveWon = wrapper->callReturnListOfPlayersAt21(wrapper);
        wrapper->callDisplayWin(dealerHasWon, playersWhoHaveWon, 21);
        return  true;
    } else if (wrapper->callGetCurrentTotal(dealer) >= 17) {
        wrapper->callDetermineWinnerFromNobody21(wrapper);
        return true;
    } else {
        cout << "Nobody has won this round" << endl;
        wrapper->callPlayDealersRound(wrapper);
        cout << "\t\tThe Dealer has placed their next card face-down." << endl<<endl;
        return false;
    }
}