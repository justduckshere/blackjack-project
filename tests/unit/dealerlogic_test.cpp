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
    Player* dealer = new Player();
    Card cardHearts("hearts", "seven");
    dealer->addCardToHand(cardHearts);
    Card cardSpades("spades", "ace");
    dealer->addCardToHand(cardSpades);
    vector<Card> hand = {cardHearts, cardSpades};
    playGame.setDealer(dealer);

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

TEST(PlayDealersRoundShould, NotIncreaseHandSizeForHandLargerThan17WithoutAce) {
    MockGame mock;

    PlayGame playGame;
    Player* dealer = new Player();
    Card cardHearts("hearts", "seven");
    dealer->addCardToHand(cardHearts);
    Card cardSpades("spades", "jack");
    dealer->addCardToHand(cardSpades);    
    vector<Card> hand = {cardHearts, cardSpades};
    playGame.setDealer(dealer);

    EXPECT_CALL(mock, callDetermineIfDealerShouldDraw(_, _))
    .Times(1)
    .WillOnce(Return(false));

    EXPECT_CALL(mock, callCheckIfHandHasAce(_))
    .Times(1)
    .WillOnce(Return(false));

    EXPECT_CALL(mock, callAddCardToHand(_, _))
    .Times(0);

    playGame.playDealersRound(&mock);

    EXPECT_EQ(playGame.getDealer()->getHand().size(), 2);
}

TEST(PlayDealersRoundShould, IncreaseHandSizeForHandLessThan17WithAce) {
    MockGame mock;
    PlayGame playGame;
    Player* dealer = new Player();
    Card cardHearts("hearts", "two");
    dealer->addCardToHand(cardHearts);
    Card cardSpades("spades", "ace");
    dealer->addCardToHand(cardSpades);
    vector<Card> hand = {cardHearts, cardSpades};
    playGame.setDealer(dealer);
    Deck* deck = new Deck();
    deck->init();
    playGame.setCurrentDeck(*deck);


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

    playGame.playDealersRound(&mock);

    EXPECT_EQ(hand.size(),3);
}

TEST(PlayDealersRoundShould, IncreaseHandSizeForHandLessThan17WithoutAce) {
    MockGame mock;

    PlayGame playGame;
    Player* dealer = new Player();
    Card cardHearts("hearts", "two");
    dealer->addCardToHand(cardHearts);
    Card cardSpades("spades", "two");
    dealer->addCardToHand(cardSpades);
    playGame.setDealer(dealer);
    vector<Card> hand = {cardHearts, cardSpades};
    Deck* deck = new Deck();
    deck->init();
    playGame.setCurrentDeck(*deck);

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

    playGame.playDealersRound(&mock);

    EXPECT_EQ(hand.size(),3);
}

TEST(DetermineIfDealerShouldDrawShould, ReturnTrueIfDealerHasLessThan16Total) {
    MockGame mock;

    PlayGame playGame;
    Player* dealer = new Player();
    Card cardHearts("hearts", "nine");
    dealer->addCardToHand(cardHearts);
    Card cardSpades("spades", "two");
    dealer->addCardToHand(cardSpades);
    playGame.setDealer(dealer);

    EXPECT_CALL(mock, callGetTotalHand(_, _))
    .Times(1)
    .WillOnce(Return(15));

    EXPECT_EQ(playGame.determineIfDealerShouldDraw(&mock, false), true);
}

TEST(DetermineIfDealerShouldDrawShould, ReturnFalseIfDealerHasMoreThan16InTotalWithNoAce) {
    MockGame mock;

    PlayGame playGame;
    Player* dealer = new Player();
    Card cardHearts("hearts", "nine");
    dealer->addCardToHand(cardHearts);
    Card cardSpades("spades", "nine");
    dealer->addCardToHand(cardSpades);
    playGame.setDealer(dealer);
    
    EXPECT_CALL(mock, callGetTotalHand(_, _))
    .Times(1)
    .WillOnce(Return(17));

    EXPECT_EQ(playGame.determineIfDealerShouldDraw(&mock, false), false);
}


TEST(DetermineIfDealerShouldDrawShould, ReturnFalseIfDealerHasMoreThan16InTotalWithAnAce) {
    MockGame mock;

    PlayGame playGame;
    Player* dealer = new Player();
    Card cardHearts("hearts", "nine");
    dealer->addCardToHand(cardHearts);
    Card cardSpades("spades", "ace");
    dealer->addCardToHand(cardSpades);
    playGame.setDealer(dealer);

    EXPECT_CALL(mock, callGetTotalHand(_, _, _))
    .Times(1)
    .WillOnce(Return(18));

    EXPECT_EQ(playGame.determineIfDealerShouldDraw(&mock, true), false);
}

TEST(DetermineIfDealerShouldDrawShould, ReturnTrueIfDealerHasLessThan16InTotalWithAnAce) {
    MockGame mock;

    PlayGame playGame;
    Player* dealer = new Player();
    Card cardHearts("hearts", "two");
    dealer->addCardToHand(cardHearts);
    Card cardSpades("spades", "ace");
    dealer->addCardToHand(cardSpades);
    playGame.setDealer(dealer);

    EXPECT_CALL(mock, callGetTotalHand(_, _, _))
    .Times(1)
    .WillOnce(Return(13));

    EXPECT_EQ(playGame.determineIfDealerShouldDraw(&mock, true), true);
}


TEST(SetDealerShould, SetTheDealerAccordingToInput) {
    PlayGame playGame;
    Player* dealer = new Player();
    Card cardHearts("hearts", "ten");
    dealer->addCardToHand(cardHearts);

    playGame.setDealer(dealer);

    EXPECT_EQ(playGame.getDealer()->getHand()[0].getSuit(), "hearts");
    EXPECT_EQ(playGame.getDealer()->getHand()[0].getValue(), "ten");

}