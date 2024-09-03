#include <gtest/gtest.h>
#include "card.h"

TEST(GetSuitShould, ReturnTheSetSuit) {
    Card card("heart", "one");
    EXPECT_EQ(card.getSuit(), "heart");
}

TEST(GetValueShould, ReturnTheSetValue) {
    Card card("heart", "one");
    EXPECT_EQ(card.getValue(), "one");
}

TEST(SetValueShould, ReturnTheSetValue) {
    Card card("heart", "one");
    card.setValue("two");
    EXPECT_EQ(card.getValue(), "two");
}

TEST(SetSuitShould, ReturnTheSetSuit) {
    Card card("heart", "one");
    card.setSuit("spade");
    EXPECT_EQ(card.getSuit(), "spade");
}

TEST(GetTrueCardValueShould, ReturnOneForAce){
    Card card("heart", "ace");
    EXPECT_EQ(card.getCardTrueValue(), 1);
}

TEST(GetTrueCardValueShould, ReturnTwoForTwo){
    Card card("heart", "two");
    EXPECT_EQ(card.getCardTrueValue(), 2);
}

TEST(GetTrueCardValueShould, ReturnThreeForThree){
    Card card("heart", "three");
    EXPECT_EQ(card.getCardTrueValue(), 3);
}

TEST(GetTrueCardValueShould, ReturnFourForFour){
    Card card("heart", "four");
    EXPECT_EQ(card.getCardTrueValue(), 4);
}

TEST(GetTrueCardValueShould, ReturnFiveForFive){
    Card card("heart", "five");
    EXPECT_EQ(card.getCardTrueValue(), 5);
}

TEST(GetTrueCardValueShould, ReturnSixForSix){
    Card card("heart", "six");
    EXPECT_EQ(card.getCardTrueValue(), 6);
}

TEST(GetTrueCardValueShould, ReturnSevenForSeven){
    Card card("heart", "seven");
    EXPECT_EQ(card.getCardTrueValue(), 7);
}

TEST(GetTrueCardValueShould, ReturnEightForEight){
    Card card("heart", "eight");
    EXPECT_EQ(card.getCardTrueValue(), 8);
}

TEST(GetTrueCardValueShould, ReturnNineForNine){
    Card card("heart", "nine");
    EXPECT_EQ(card.getCardTrueValue(), 9);
}

TEST(GetTrueCardValueShould, ReturnTenForTen){
    Card card("heart", "ten");
    EXPECT_EQ(card.getCardTrueValue(), 10);
}

TEST(GetTrueCardValueShould, ReturnTenForJack){
    Card card("heart", "jack");
    EXPECT_EQ(card.getCardTrueValue(), 10);
}

TEST(GetTrueCardValueShould, ReturnTenForQueen){
    Card card("heart", "queen");
    EXPECT_EQ(card.getCardTrueValue(), 10);
}

TEST(GetTrueCardValueShould, ReturnTenForKing){
    Card card("heart", "king");
    EXPECT_EQ(card.getCardTrueValue(), 10);
}