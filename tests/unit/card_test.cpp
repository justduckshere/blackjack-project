#include <gtest/gtest.h>
#include "card.h"

TEST(Card_GetSuitShould, ReturnTheSetSuit) {
    Card card("heart", "one");
    EXPECT_EQ(card.getSuit(), "heart");
}

TEST(Card_GetValueShould, ReturnTheSetValue) {
    Card card("heart", "one");
    EXPECT_EQ(card.getValue(), "one");
}

TEST(Card_SetValueShould, ReturnTheSetValue) {
    Card card("heart", "one");
    card.setValue("two");
    EXPECT_EQ(card.getValue(), "two");
}

TEST(Card_SetSuitShould, ReturnTheSetSuit) {
    Card card("heart", "one");
    card.setSuit("spade");
    EXPECT_EQ(card.getSuit(), "spade");
}

TEST(Card_GetTrueCardValueShould, ReturnOneForAce){
    Card card("heart", "ace");
    EXPECT_EQ(card.getCardTrueValue(), 1);
}

TEST(Card_GetTrueCardValueShould, ReturnTwoForTwo){
    Card card("heart", "two");
    EXPECT_EQ(card.getCardTrueValue(), 2);
}

TEST(Card_GetTrueCardValueShould, ReturnThreeForThree){
    Card card("heart", "three");
    EXPECT_EQ(card.getCardTrueValue(), 3);
}

TEST(Card_GetTrueCardValueShould, ReturnFourForFour){
    Card card("heart", "four");
    EXPECT_EQ(card.getCardTrueValue(), 4);
}

TEST(Card_GetTrueCardValueShould, ReturnFiveForFive){
    Card card("heart", "five");
    EXPECT_EQ(card.getCardTrueValue(), 5);
}

TEST(Card_GetTrueCardValueShould, ReturnSixForSix){
    Card card("heart", "six");
    EXPECT_EQ(card.getCardTrueValue(), 6);
}

TEST(Card_GetTrueCardValueShould, ReturnSevenForSeven){
    Card card("heart", "seven");
    EXPECT_EQ(card.getCardTrueValue(), 7);
}

TEST(Card_GetTrueCardValueShould, ReturnEightForEight){
    Card card("heart", "eight");
    EXPECT_EQ(card.getCardTrueValue(), 8);
}

TEST(Card_GetTrueCardValueShould, ReturnNineForNine){
    Card card("heart", "nine");
    EXPECT_EQ(card.getCardTrueValue(), 9);
}

TEST(Card_GetTrueCardValueShould, ReturnTenForTen){
    Card card("heart", "ten");
    EXPECT_EQ(card.getCardTrueValue(), 10);
}

TEST(Card_GetTrueCardValueShould, ReturnTenForJack){
    Card card("heart", "jack");
    EXPECT_EQ(card.getCardTrueValue(), 10);
}

TEST(Card_GetTrueCardValueShould, ReturnTenForQueen){
    Card card("heart", "queen");
    EXPECT_EQ(card.getCardTrueValue(), 10);
}

TEST(Card_GetTrueCardValueShould, ReturnTenForKing){
    Card card("heart", "king");
    EXPECT_EQ(card.getCardTrueValue(), 10);
}