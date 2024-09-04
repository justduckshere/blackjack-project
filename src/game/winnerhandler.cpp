#include "playgame.h"


void PlayGame::determineWinnerFromNobody21(PlayGameWrapper *wrapper) {
    wrapper->callSetHighestValidHandValueForPlayer(wrapper, dealer, true);
    pair<int, vector<int>> highest = wrapper->callGetListOfPlayersWithHighestScores(wrapper);
    int dealerTotal = wrapper->callGetCurrentTotal(dealer);

    if (dealerTotal > highest.first) {
        wrapper->callDisplayWin(true, {}, dealerTotal); 
    } else if(dealerTotal == highest.first) {
        wrapper->callDisplayWin(true, highest.second, highest.first); 
    } else {
        wrapper->callDisplayWin(false, highest.second, highest.first); 
    }
}

pair<int, vector<int>> PlayGame::getListOfPlayersWithHighestScores(PlayGameWrapper *wrapper) {
    int highestScore =0;
    vector<int> highestScoresPlayerId = {}; 

    for (int i =0; i < getPlayerList().size(); i++) {
        int playersTotal = wrapper->callGetCurrentTotal(getPlayerList()[i]);
        if (playersTotal > highestScore && playersTotal <=21) {
            highestScore = playersTotal;
            highestScoresPlayerId = {};
            highestScoresPlayerId.push_back(i);
        } else if (playersTotal == highestScore) {
            highestScoresPlayerId.push_back(i);
        }
    }
    return make_pair(highestScore, highestScoresPlayerId);
}

void PlayGame::displayWin(bool dealerHasWon, vector<int> playersWhoHaveWon, int score) {
    if(dealerHasWon == true && playersWhoHaveWon.size() !=0){
        cout << "We have a tie!" << endl;
        for (int i =0; i < playersWhoHaveWon.size(); i++){
            cout << "Player " << playersWhoHaveWon[i]+1 << " has won with a score of: "<< score << endl <<endl;
        }
        cout << "And Dealer has also achieved " << score << endl <<endl;
    } else if (playersWhoHaveWon.size() > 1) {
        cout << "We have a tie!" << endl;
        for (int i =0; i < playersWhoHaveWon.size(); i++){
            cout << "Player " << playersWhoHaveWon[i]+1 << " has won with a score of: "<< score << endl <<endl;
        }
    } else if (dealerHasWon == true) {
        cout<< "Dealer has won with a score of "<< score <<endl;
    } else {
        for (int i =0; i < playersWhoHaveWon.size(); i++){
            cout << "Player " << playersWhoHaveWon[i]+1<< " has won and with a score of "<< score << endl <<endl;
        }
    }
}

void PlayGame::setHighestValidHandValueForPlayer(PlayGameWrapper *wrapper,Player* player, bool isDealer) {
    bool hasAce = wrapper->callCheckIfHandHasAce(player->getHand());
    if (hasAce == true) {
        int elevenCount = wrapper->callGetTotalHand(wrapper, player->getHand(), 11);
        int oneCount = wrapper->callGetTotalHand(wrapper, player->getHand(), 1);
        if (elevenCount < 21 || isDealer == true) {
            player->setCurrentTotal(elevenCount);
        } else {
            player->setCurrentTotal(oneCount);
        }
    } else {
        player->setCurrentTotal(wrapper->callGetTotalHand(wrapper, player->getHand()));
    }
}


