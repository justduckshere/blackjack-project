#include <gtest/gtest.h>
#include "deck.h"

TEST(DeckGetDeckSizeShould, Be52AfterInit) {
    Deck deck;
    deck.init();
    EXPECT_EQ(deck.getDeck().size(), 52);
}

TEST(DeckGetDeckSizeShould, Be0WithoutInit) {
    Deck deck;
    EXPECT_EQ(deck.getDeck().size(), 0);
}


TEST(DeckRemovePlayedCardShould, HaveADifferentLastElement) {
    Deck deck;
    deck.init();
    Card lastElement = deck.getDeck().back();
    deck.removePlayedCard();
    ASSERT_TRUE(lastElement.getValue() != deck.getDeck().back().getValue());
}

TEST(DeckRemovePlayedCardShould, HaveADeckSizeOf51WhenCalledTwice) {
    Deck deck;
    deck.init();
    deck.removePlayedCard();
    ASSERT_TRUE(deck.getDeck().size() == 51);
}

TEST(DeckRemovePlayedCardShould, HaveADeckSizeOf50WhenCalledTwice) {
    Deck deck;
    deck.init();
    deck.removePlayedCard();
    deck.removePlayedCard();
    ASSERT_TRUE(deck.getDeck().size() == 50);
}


//this is ugly... sorry
TEST(DeckShuffledDeckShould, NeverBeTheSameAsInputDeck) {
    Deck deck;
    Deck newDeck;
    deck.shuffle();
    vector<Card> deckCards = deck.getDeck();
    vector<Card> newDeckCards = newDeck.getDeck();
    int equalCount = 0;
    for (int i =0; i < size(deckCards); i++) {
        if (deckCards[i].getSuit() == newDeckCards[i].getSuit() && 
            deckCards[i].getValue() == newDeckCards[i].getValue()
        ) {
            equalCount++; 
        }
    }

    ASSERT_FALSE(equalCount == 52);
}