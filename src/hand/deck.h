#ifndef DECK_H
#define DECK_H

#include <vector>
#include <random>
#include <algorithm>
#include "card.h"

using namespace std;

class Deck {
public:   
    Deck();
    void init();
    string suits[4] = {"hearts", "diamonds", "clubs", "spades"};
    string values[13] = {"ace", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "jack", "queen", "king"};
    vector<Card> getDeck();
    void shuffle();
    void removePlayedCard();

private:
    static vector<Card> cardsInDeck;
};

#endif

