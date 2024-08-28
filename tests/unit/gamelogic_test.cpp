#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "game/playgame.h"
#include "wrapper.h"
#include <vector>
#include <sstream>
using namespace std;
using ::testing::Return;
using ::testing::_;

TEST(VerifyHandHasWonShould, ReturnTrueWhenHandIs21WithoutAce) {
    MockGame mock;
    PlayGame playGame;
    vector<Card> hand = {};

    EXPECT_CALL(mock, callCheckIfHandHasWon(_, _))
    .Times(1)
    .WillOnce(Return(true));

    EXPECT_CALL(mock, callCheckIfHandHasAce(_))
    .Times(1)
    .WillOnce(Return(false));
    
    bool actual = playGame.verifyHandHasWon(&mock, hand);
    EXPECT_EQ(actual, true);  
}

TEST(VerifyHandHasWonShould, ReturnFalseWhenHandIsnt21WithoutAce) {
    MockGame mock;
    PlayGame playGame;

    vector<Card> hand = {};

    EXPECT_CALL(mock, callCheckIfHandHasWon(_, _))
    .Times(1)
    .WillOnce(Return(false));

    EXPECT_CALL(mock, callCheckIfHandHasAce(_))
    .Times(1)
    .WillOnce(Return(false));
    
    bool actual = playGame.verifyHandHasWon(&mock, hand);
    EXPECT_EQ(actual, false);  
}

TEST(VerifyHandHasWonShould, ReturnTrueWhenHandIs21WithOneAceAsElevenButStillEqualTo21) {
    MockGame mock;
    PlayGame playGame;

    vector<Card> hand = {};

    EXPECT_CALL(mock, callCheckIfHandHasWonWithAce(_, _, 1))
    .Times(1)
    .WillOnce(Return(false));

    EXPECT_CALL(mock, callCheckIfHandHasWonWithAce(_, _, 11))
    .Times(1)
    .WillOnce(Return(true));

    EXPECT_CALL(mock, callCheckIfHandHasAce(_))
    .Times(1)
    .WillOnce(Return(true));
    

    bool actual = playGame.verifyHandHasWon(&mock, hand);
    EXPECT_EQ(actual, true);    
}

TEST(VerifyHandHasWonShould, ReturnTrueWhenHandIs21WithAceAsOne) {
    MockGame mock;
    PlayGame playGame;

    vector<Card> hand = {};

    EXPECT_CALL(mock, callCheckIfHandHasWonWithAce(_, _, 1))
    .Times(1)
    .WillOnce(Return(true));

    EXPECT_CALL(mock, callCheckIfHandHasAce(_))
    .Times(1)
    .WillOnce(Return(true));
    

    bool actual = playGame.verifyHandHasWon(&mock, hand);
    EXPECT_EQ(actual, true);    
}


TEST(CheckIfHandHasAceShould, ReturnFalseWhenNoAceIsInHand) {
    PlayGame playGame;
    Player* player = new Player();
    Card cardHearts("hearts", "ten");
    player->addCardToHand(cardHearts);

    bool actual = playGame.checkIfHandHasAce(player->getHand());

    EXPECT_EQ(actual, false);
}

TEST(CheckIfHandHasAceShould, ReturnTrueWhenAceIsInHand) {
    PlayGame playGame;
    Player* player = new Player();
    Card cardHearts("hearts", "ten");
    player->addCardToHand(cardHearts);
    Card cardClubs("clubs", "ace");
    player->addCardToHand(cardClubs);

    bool actual = playGame.checkIfHandHasAce(player->getHand());

    EXPECT_EQ(actual, true);
}


TEST(CheckIfHandHasWonShould, ReturnFalseWhenHandIsnt21WithAceInHand) {
    MockGame mock;

    PlayGame playGame;
    Card cardHearts("hearts", "ace");
    Card cardSpades("spades", "five");
    vector<Card> hand = {cardHearts, cardSpades};

    EXPECT_CALL(mock, callGetCardTrueValue(_))
    .Times(2)
    .WillOnce(Return(1))
    .WillOnce(Return(5));

    bool actual = playGame.checkIfHandHasWon(&mock, hand, 1);
    EXPECT_EQ(actual, false);    
}

TEST(CheckIfHandHasWonShould, ReturnTrueWhenHandIs21WithAceAsOne) {
    MockGame mock;

    PlayGame playGame;
    Card cardHearts("hearts", "ace");
    Card cardSpades("spades", "five");
    Card cardDiamonds("diamonds", "five");
    Card cardClubs("clubs", "ten");
    vector<Card> hand = {cardHearts, cardSpades, cardDiamonds, cardClubs};

    EXPECT_CALL(mock, callGetCardTrueValue(_))
    .Times(4)
    .WillOnce(Return(1))
    .WillOnce(Return(5))
    .WillOnce(Return(5))
    .WillOnce(Return(10));

    bool actual = playGame.checkIfHandHasWon(&mock, hand, 1);
    EXPECT_EQ(actual, true);    
}

TEST(CheckIfHandHasWonShould, ReturnTrueWhenHandIs21WithoutAce) {
    MockGame mock;

    PlayGame playGame;
    Card cardHearts("hearts", "five");
    Card cardSpades("spades", "five");
    Card cardDiamonds("diamonds", "five");
    Card cardClubs("clubs", "six");
    vector<Card> hand = {cardHearts, cardSpades, cardDiamonds, cardClubs};

    EXPECT_CALL(mock, callGetCardTrueValue(_))
    .Times(4)
    .WillOnce(Return(5))
    .WillOnce(Return(5))
    .WillOnce(Return(5))
    .WillOnce(Return(6));

    bool actual = playGame.checkIfHandHasWon(&mock, hand);
    EXPECT_EQ(actual, true);    
}

TEST(CheckIfHandHasWonShould, ReturnFalseWhenHandIsnt21WithoutAce) {
    MockGame mock;
    PlayGame playGame;
    Card cardHearts("hearts", "five");
    vector<Card> hand = {cardHearts};

    EXPECT_CALL(mock, callGetCardTrueValue(_))
    .Times(1)
    .WillOnce(Return(10));

    bool actual = playGame.checkIfHandHasWon(&mock, hand);
    EXPECT_EQ(actual, false);    
}


TEST(VerifyAnyPlayerHasAchieved21Should, ReturnZeroIfOnePlayerHasWon){
    MockGame mock;

    PlayGame playGame;
    Player* player = new Player();
    Player* player2 = new Player();
    vector<Player*> players = {player, player2};
    playGame.setPlayerList(players);

    EXPECT_CALL(mock, callVerifyHandHasWon(_, _))
    .Times(2)
    .WillOnce(Return(true))
    .WillOnce(Return(false));

    vector<int> actual = playGame.verifyAnyPlayerHasAchieved21(&mock);

    EXPECT_EQ(actual.back(), 0);    
}

TEST(VerifyAnyPlayerHasAchieved21Should, ReturnZeroIfNoPlayersHaveWon){
    MockGame mock;

    PlayGame playGame;
    Player* player = new Player();
    Player* player2 = new Player();
    vector<Player*> players = {player, player2};
    playGame.setPlayerList(players);

    EXPECT_CALL(mock, callVerifyHandHasWon(_, _))
    .Times(2)
    .WillOnce(Return(false))
    .WillOnce(Return(false));

    vector<int> actual = playGame.verifyAnyPlayerHasAchieved21(&mock);

    EXPECT_EQ(actual.size(),0);    
}


TEST(VerifyAnyPlayerHasAchieved21Should, ReturnOneIfSecondOfTwoPlayersHaveWon){
    MockGame mock;

    PlayGame playGame;
    Player* player = new Player();
    Player* player2 = new Player();
    vector<Player*> players = {player, player2};
    playGame.setPlayerList(players);

    EXPECT_CALL(mock, callVerifyHandHasWon(_, _))
    .Times(2)
    .WillOnce(Return(false))
    .WillOnce(Return(true));

    
    vector<int> actual = playGame.verifyAnyPlayerHasAchieved21(&mock);
    EXPECT_EQ(actual.back(), 1);    
}


TEST(CheckIfHandHasGoneBustShould, ReturnFalseWhenUnder21) {
    MockGame mock;
    PlayGame playGame;
    Card cardHearts("hearts", "ten");
    Card cardSpades("spades", "ten");
    Card cardClubs("clubs", "ace");
    vector<Card> hand = {cardHearts, cardSpades, cardClubs};

    EXPECT_CALL(mock, callGetCardTrueValue(_))
    .Times(3)
    .WillOnce(Return(1))
    .WillOnce(Return(1))
    .WillOnce(Return(1));

    bool actual = playGame.checkIfHandHasGoneBust(&mock, hand);

    EXPECT_EQ(actual, false);
}

TEST(CheckIfHandHasGoneBustShould, ReturnTrueWhenOver21) {
    MockGame mock;
    PlayGame playGame;
    Card cardHearts("hearts", "ten");
    Card cardSpades("spades", "ten");
    Card cardClubs("clubs", "ace");
    vector<Card> hand = {cardHearts, cardSpades, cardClubs};

    EXPECT_CALL(mock, callGetCardTrueValue(_))
    .Times(3)
    .WillOnce(Return(10))
    .WillOnce(Return(10))
    .WillOnce(Return(10));

    bool actual = playGame.checkIfHandHasGoneBust(&mock, hand);

    EXPECT_EQ(actual, true);
}

TEST(CheckIfHandHasGoneBustShould, ReturnFalseWhenExactly21) {
    MockGame mock;
    PlayGame playGame;
    Card cardHearts("hearts", "ten");
    Card cardSpades("spades", "ten");
    Card cardClubs("clubs", "ace");
    vector<Card> hand = {cardHearts, cardSpades, cardClubs};
    
    EXPECT_CALL(mock, callGetCardTrueValue(_))
    .Times(3)
    .WillOnce(Return(1))
    .WillOnce(Return(10))
    .WillOnce(Return(10));

    bool actual = playGame.checkIfHandHasGoneBust(&mock, hand);

    EXPECT_EQ(actual, false);
}


TEST(CheckIfAllPlayersHaveGoneBustShould, ReturnFalseWhenOnePlayerIsntBust) {
    MockGame mock;
    PlayGame playGame;   
    Player* player = new Player();
    Player* player2 = new Player();
    vector<Player*> players = {player, player2};
    playGame.setPlayerList(players);
    vector<Card> hand = {};

    EXPECT_CALL(mock, callCheckIfHandHasGoneBust(_, _))
    .Times(2)
    .WillOnce(Return(true))
    .WillOnce(Return(false));

    bool actual = playGame.checkIfAllPlayersHaveGoneBust(&mock);

    EXPECT_EQ(actual, false);
}

TEST(CheckIfAllPlayersHaveGoneBustShould, ReturnFalseOnFirstTryWhenAllPlayersAreBust) {
    MockGame mock;
    PlayGame playGame;   
    Player* player = new Player();
    Player* player2 = new Player();
    vector<Player*> players = {player, player2};
    playGame.setPlayerList(players);
    vector<Card> hand = {};

    EXPECT_CALL(mock, callCheckIfHandHasGoneBust(_, _))
    .Times(1)
    .WillOnce(Return(false));

    bool actual = playGame.checkIfAllPlayersHaveGoneBust(&mock);

    EXPECT_EQ(actual, false);
}

TEST(CheckIfAllPlayersHaveGoneBustShould, ReturnTrueWhenAllPlayersAreBust) {
    MockGame mock;
    PlayGame playGame;   
    Player* player = new Player();
    Player* player2 = new Player();
    vector<Player*> players = {player, player2};
    playGame.setPlayerList(players);
    vector<Card> hand = {};

    EXPECT_CALL(mock, callCheckIfHandHasGoneBust(_, _))
    .Times(2)
    .WillRepeatedly(Return(true));

    bool actual = playGame.checkIfAllPlayersHaveGoneBust(&mock);

    EXPECT_EQ(actual, true);
}