#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "game/playgame.h"
#include "hand/deck.h"
#include <sstream>
#include "wrapper.h"

using namespace std;
using ::testing::Return;
using ::testing::_;

TEST(DealerLogic_PlayDealersRoundShould, NotIncreaseHandSizeForHandLargerThan17WithAce) {
    MockGame mock;
    PlayGame playGame;
    Card cardHearts("hearts", "seven");
    Card cardSpades("spades", "ace");
    vector<Card> hand = {cardHearts, cardSpades};

    EXPECT_CALL(mock, callDetermineIfDealerShouldDraw(_, _))
    .Times(1)
    .WillOnce(Return(false));

    EXPECT_CALL(mock, callCheckIfHandHasAce(_))
    .Times(1)
    .WillOnce(Return(true));

    EXPECT_CALL(mock, callAddCardToHand(_, _))
    .Times(0);

    playGame.playDealersRound(&mock);

    EXPECT_EQ(hand.size(), 2);
}

TEST(DealerLogic_PlayDealersRoundShould, NotIncreaseHandSizeForHandLargerThan17WithoutAce) {
    MockGame mock;

    PlayGame playGame;
    Card cardHearts("hearts", "seven");
    Card cardSpades("spades", "jack");
    vector<Card> hand = {cardHearts, cardSpades};

    EXPECT_CALL(mock, callDetermineIfDealerShouldDraw(_, _))
    .Times(1)
    .WillOnce(Return(false));

    EXPECT_CALL(mock, callCheckIfHandHasAce(_))
    .Times(1)
    .WillOnce(Return(false));

    EXPECT_CALL(mock, callAddCardToHand(_, _))
    .Times(0);

    playGame.playDealersRound(&mock);

    EXPECT_EQ(hand.size(), 2);
}

TEST(DealerLogic_PlayDealersRoundShould, IncreaseHandSizeForHandLessThan17WithAce) {
    MockGame mock;
    PlayGame playGame;
    Card cardHearts("hearts", "two");
    Card cardSpades("spades", "ace");
    vector<Card> hand = {cardHearts, cardSpades};
    vector<Card> deck = {cardHearts, cardSpades};

    EXPECT_CALL(mock, callDetermineIfDealerShouldDraw(_, _))
    .Times(1)
    .WillOnce(Return(true));

    EXPECT_CALL(mock, callCheckIfHandHasAce(_))
    .Times(1)
    .WillOnce(Return(true));

    EXPECT_CALL(mock, callAddCardToHand(_, _))
    .Times(1)
    .WillOnce([&hand](Player* dealer, Card cardExample){
        Card cardDiamond("diamonds", "two");
        hand.push_back(cardDiamond);
    });

    EXPECT_CALL(mock, callGetDeck(_))
    .Times(1)
    .WillOnce(Return(deck));

    playGame.playDealersRound(&mock);

    EXPECT_EQ(hand.size(),3);
}

TEST(DealerLogic_PlayDealersRoundShould, IncreaseHandSizeForHandLessThan17WithoutAce) {
    MockGame mock;
    PlayGame playGame;
    Card cardHearts("hearts", "two");
    Card cardSpades("spades", "two");
    vector<Card> hand = {cardHearts, cardSpades};
    vector<Card> deck = {cardHearts, cardSpades};

    EXPECT_CALL(mock, callDetermineIfDealerShouldDraw(_, _))
    .Times(1)
    .WillOnce(Return(true));

    EXPECT_CALL(mock, callCheckIfHandHasAce(_))
    .Times(1)
    .WillOnce(Return(false));

    EXPECT_CALL(mock, callAddCardToHand(_, _))
    .Times(1)
    .WillOnce([&hand](Player* dealer, Card cardExample){
        Card cardDiamond("diamonds", "two");
        hand.push_back(cardDiamond);
    });

    EXPECT_CALL(mock, callGetDeck(_))
    .Times(1)
    .WillOnce(Return(deck));

    playGame.playDealersRound(&mock);

    EXPECT_EQ(hand.size(),3);
}


TEST(DealerLogic_DetermineIfDealerShouldDrawShould, ReturnTrueIfDealerHasLessThan17TotalWithAce) {
    MockGame mock;

    PlayGame playGame;
    Card cardHearts("hearts", "nine");
    Card cardSpades("spades", "two");

    EXPECT_CALL(mock, callGetTotalHand(_, _))
    .Times(1)
    .WillOnce(Return(16));

    EXPECT_EQ(playGame.determineIfDealerShouldDraw(&mock, false), true);
}

TEST(DealerLogic_DetermineIfDealerShouldDrawShould, ReturnFalseIfDealerHasMoreThan17InTotalWithNoAce) {
    MockGame mock;

    PlayGame playGame;
    Card cardHearts("hearts", "nine");
    Card cardSpades("spades", "nine");
    
    EXPECT_CALL(mock, callGetTotalHand(_, _))
    .Times(1)
    .WillOnce(Return(17));

    EXPECT_EQ(playGame.determineIfDealerShouldDraw(&mock, false), false);
}

TEST(DealerLogic_DetermineIfDealerShouldDrawShould, ReturnFalseIfDealerHasMoreThan17InTotalWithAnAce) {
    MockGame mock;

    PlayGame playGame;
    Card cardHearts("hearts", "nine");
    Card cardSpades("spades", "ace");

    EXPECT_CALL(mock, callGetTotalHand(_, _, _))
    .Times(1)
    .WillOnce(Return(18));

    EXPECT_EQ(playGame.determineIfDealerShouldDraw(&mock, true), false);
}

TEST(DealerLogic_DetermineIfDealerShouldDrawShould, ReturnTrueIfDealerHasLessThan1InTotalWithAnAce) {
    MockGame mock;

    PlayGame playGame;
    Card cardHearts("hearts", "two");
    Card cardSpades("spades", "ace");

    EXPECT_CALL(mock, callGetTotalHand(_, _, _))
    .Times(1)
    .WillOnce(Return(13));

    EXPECT_EQ(playGame.determineIfDealerShouldDraw(&mock, true), true);
}