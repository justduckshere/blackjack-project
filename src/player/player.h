#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <iostream>
#include "../hand/card.h"

class Player {

public:
    Player();
    void addCardToHand(Card card);
    vector<Card> getHand();
    void setPlayerHasGoneBust();
    bool getPlayerHasGoneBust();
    void setCurrentTotal(int total);
    int getCurrentTotal();
    void displayHand();

private:
    vector<Card> hand;
    int currentTotal;
    bool lost;
    bool goneBust;

};

#endif