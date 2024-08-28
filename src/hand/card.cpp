#include "card.h"

void Card::setSuit(string suit) {
    this->suit = suit;
}
void Card::setValue(string value) {
    this->value = value;
}
string Card::getSuit(){
    return this->suit;
}
string Card::getValue(){
    return this->value;
}

Card::Card(string suit, string value){
    this->suit = suit;
    this->value = value;
}

int Card::getCardTrueValue(){
    string faceValue = this->value;
    if(faceValue == "ace") {
        return 1;
    } else if ( faceValue == "two"){
        return 2;
    } else if ( faceValue == "three"){
        return 3;
    } else if ( faceValue == "four"){
        return 4;
    } else if ( faceValue == "five"){
        return 5;
    } else if ( faceValue == "six"){
        return 6;
    } else if ( faceValue == "seven"){
        return 7;
    } else if ( faceValue == "eight"){
        return 8;
    } else if ( faceValue == "nine"){
        return 9;
    } 
    return 10;
}