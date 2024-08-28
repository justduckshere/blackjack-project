#ifndef CARD_H
#define CARD_H
#include <string>

using namespace std;

class Card {
public:
    Card(string suit, string value);
    void setSuit(string suit);
    void setValue(string value);
    string getSuit();
    string getValue();
    int getCardTrueValue();

private:
    string value;
    string suit;
};

#endif