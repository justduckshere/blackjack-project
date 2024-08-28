#include "deck.h"
#include <iostream>

using namespace std;

vector<Card> Deck::cardsInDeck;

Deck::Deck() {
}

void Deck::init(){
    for (int i = 0; i < size(Deck::suits);i++) {
        for (int j= 0; j <size(Deck::values); j++) {
            Card newCard(suits[i], values[j]);
            cardsInDeck.push_back(newCard);
        }
    }
}

vector<Card> Deck::getDeck(){
    return cardsInDeck;
}

void Deck::shuffle(){
    random_device rd; 
    mt19937 g(rd()); 
    std::shuffle(cardsInDeck.begin(), cardsInDeck.end(),g);
}

void Deck::removePlayedCard() {
    cardsInDeck.pop_back();
}

