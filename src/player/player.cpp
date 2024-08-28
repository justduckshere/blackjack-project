#include "player.h"

Player::Player(){
    this->goneBust = false;
}

void Player::addCardToHand(Card card) {
    hand.insert(hand.begin(), card);
}

vector<Card> Player::getHand(){
    return this->hand;
}

void Player::setPlayerHasGoneBust() {
    this->goneBust = true;
}

bool Player::getPlayerHasGoneBust() {
    return this->goneBust;
}


void Player::setCurrentTotal(int total){
    this->currentTotal = total;
}

int Player::getCurrentTotal(){
    return this->currentTotal;
}

void Player::displayHand(){
    for (int i = 0; i < getHand().size(); i++) {
        cout << "a " << getHand()[i].getValue() << " of "<< getHand()[i].getSuit(); 
        if (i != getHand().size() -1) {
            cout << ", ";
        } else {
            cout << endl<< endl;
        }
    }
}