#include <gtest/gtest.h>
#include "card.h"

TEST(CardGetSuitShould, ReturnTheSetSuit) {
    Card card("heart", "one");
    EXPECT_EQ(card.getSuit(), "heart");
}

TEST(CardGetValueShould, ReturnTheSetValue) {
    Card card("heart", "one");
    EXPECT_EQ(card.getValue(), "one");
}

TEST(CardSetValueShould, ReturnTheSetValue) {
    Card card("heart", "one");
    card.setValue("two");
    EXPECT_EQ(card.getValue(), "two");
}

TEST(CardSetSuitShould, ReturnTheSetSuit) {
    Card card("heart", "one");
    card.setSuit("spade");
    EXPECT_EQ(card.getSuit(), "spade");
}

TEST(CardGetTrueCardValueShould, ReturnOneForAce){
    Card card("heart", "ace");
    EXPECT_EQ(card.getCardTrueValue(), 1);
}

TEST(CardGetTrueCardValueShould, ReturnTwoForTwo){
    Card card("heart", "two");
    EXPECT_EQ(card.getCardTrueValue(), 2);
}

TEST(CardGetTrueCardValueShould, ReturnThreeForThree){
    Card card("heart", "three");
    EXPECT_EQ(card.getCardTrueValue(), 3);
}

TEST(CardGetTrueCardValueShould, ReturnFourForFour){
    Card card("heart", "four");
    EXPECT_EQ(card.getCardTrueValue(), 4);
}

TEST(CardGetTrueCardValueShould, ReturnFiveForFive){
    Card card("heart", "five");
    EXPECT_EQ(card.getCardTrueValue(), 5);
}

TEST(CardGetTrueCardValueShould, ReturnSixForSix){
    Card card("heart", "six");
    EXPECT_EQ(card.getCardTrueValue(), 6);
}

TEST(CardGetTrueCardValueShould, ReturnSevenForSeven){
    Card card("heart", "seven");
    EXPECT_EQ(card.getCardTrueValue(), 7);
}

TEST(CardGetTrueCardValueShould, ReturnEightForEight){
    Card card("heart", "eight");
    EXPECT_EQ(card.getCardTrueValue(), 8);
}

TEST(CardGetTrueCardValueShould, ReturnNineForNine){
    Card card("heart", "nine");
    EXPECT_EQ(card.getCardTrueValue(), 9);
}

TEST(CardGetTrueCardValueShould, ReturnTenForTen){
    Card card("heart", "ten");
    EXPECT_EQ(card.getCardTrueValue(), 10);
}

TEST(CardGetTrueCardValueShould, ReturnTenForJack){
    Card card("heart", "jack");
    EXPECT_EQ(card.getCardTrueValue(), 10);
}

TEST(CardGetTrueCardValueShould, ReturnTenForQueen){
    Card card("heart", "queen");
    EXPECT_EQ(card.getCardTrueValue(), 10);
}

TEST(CardGetTrueCardValueShould, ReturnTenForKing){
    Card card("heart", "king");
    EXPECT_EQ(card.getCardTrueValue(), 10);
}