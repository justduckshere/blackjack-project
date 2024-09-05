#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "game/playgame.h"
#include "../wrapper.h"
#include <vector>
#include <sstream>
using namespace std;
using ::testing::Return;
using ::testing::_;

TEST(GameLogic_VerifyHandis21Should, ReturnTrueWhenHandIs21WithoutAce) {
    MockGame mock;
    PlayGame playGame;
    vector<Card> hand = {};

    EXPECT_CALL(mock, callHandis21(_, _))
    .Times(1)
    .WillOnce(Return(true));

    EXPECT_CALL(mock, callHandHasAce(_))
    .Times(1)
    .WillOnce(Return(false));
    
    bool actual = playGame.verifyHandis21(&mock, hand);
    EXPECT_EQ(actual, true);  
}

TEST(GameLogic_VerifyHandis21Should, ReturnFalseWhenHandIsnt21WithoutAce) {
    MockGame mock;
    PlayGame playGame;

    vector<Card> hand = {};

    EXPECT_CALL(mock, callHandis21(_, _))
    .Times(1)
    .WillOnce(Return(false));

    EXPECT_CALL(mock, callHandHasAce(_))
    .Times(1)
    .WillOnce(Return(false));
    
    bool actual = playGame.verifyHandis21(&mock, hand);
    EXPECT_EQ(actual, false);  
}

TEST(GameLogic_VerifyHandis21Should, ReturnTrueWithOneAceAsElevenAndEqualTo21) {
    MockGame mock;
    PlayGame playGame;

    vector<Card> hand = {};

    EXPECT_CALL(mock, callHandHasAce(_))
    .Times(1)
    .WillOnce(Return(true));

    EXPECT_CALL(mock, callHandis21WithAce(_, _, 1))
    .Times(1)
    .WillOnce(Return(false));

    EXPECT_CALL(mock, callHandis21WithAce(_, _, 11))
    .Times(1)
    .WillOnce(Return(true));

    bool actual = playGame.verifyHandis21(&mock, hand);
    EXPECT_EQ(actual, true);    
}

TEST(GameLogic_VerifyHandis21Should, ReturnTrueWithOneAceAsOneAndEqualTo21) {
    MockGame mock;
    PlayGame playGame;

    vector<Card> hand = {};

    EXPECT_CALL(mock, callHandHasAce(_))
    .Times(1)
    .WillOnce(Return(true));

    EXPECT_CALL(mock, callHandis21WithAce(_, _, 1))
    .Times(1)
    .WillOnce(Return(true));
    

    bool actual = playGame.verifyHandis21(&mock, hand);
    EXPECT_EQ(actual, true);    
}

TEST(GameLogic_VerifyHandis21Should, ReturnFalseWithAceAndNotEqualTo21) {
    MockGame mock;
    PlayGame playGame;

    vector<Card> hand = {};

    EXPECT_CALL(mock, callHandis21WithAce(_, _, 1))
    .Times(1)
    .WillRepeatedly(Return(false));

    EXPECT_CALL(mock, callHandis21WithAce(_, _, 11))
    .Times(1)
    .WillRepeatedly(Return(false));

    EXPECT_CALL(mock, callHandHasAce(_))
    .Times(1)
    .WillOnce(Return(true));
    

    bool actual = playGame.verifyHandis21(&mock, hand);
    EXPECT_EQ(actual, false);    
}



TEST(GameLogic_HandHasAceShould, ReturnFalseWhenNoAceIsInHand) {
    PlayGame playGame;
    Player* player = new Player();
    Card cardHearts("hearts", "ten");
    player->addCardToHand(cardHearts);

    bool actual = playGame.handHasAce(player->getHand());

    EXPECT_EQ(actual, false);
}

TEST(GameLogic_HandHasAceShould, ReturnTrueWhenAceIsInHand) {
    PlayGame playGame;
    Player* player = new Player();
    Card cardHearts("hearts", "ten");
    player->addCardToHand(cardHearts);
    Card cardClubs("clubs", "ace");
    player->addCardToHand(cardClubs);

    bool actual = playGame.handHasAce(player->getHand());

    EXPECT_EQ(actual, true);
}


TEST(GameLogic_Handis21Should, ReturnFalseWhenHandIsnt21WithAceInHand) {
    MockGame mock;

    PlayGame playGame;
    Card cardHearts("hearts", "ace");
    Card cardSpades("spades", "five");
    vector<Card> hand = {cardHearts, cardSpades};

    EXPECT_CALL(mock, callGetCardTrueValue(_))
    .Times(2)
    .WillOnce(Return(1))
    .WillOnce(Return(5));

    bool actual = playGame.handis21(&mock, hand, 1);
    EXPECT_EQ(actual, false);    
}

TEST(GameLogic_Handis21Should, ReturnFalseWhenHandIsnt21WithoutAce) {
    MockGame mock;
    PlayGame playGame;
    Card cardHearts("hearts", "five");
    vector<Card> hand = {cardHearts};

    EXPECT_CALL(mock, callGetCardTrueValue(_))
    .Times(1)
    .WillOnce(Return(10));

    bool actual = playGame.handis21(&mock, hand);
    EXPECT_EQ(actual, false);    
}

TEST(GameLogic_Handis21Should, ReturnFalseWhenHandIsnt21WithMultipleAces) {
    MockGame mock;
    PlayGame playGame;
    Card cardHearts("hearts", "ace");
    Card cardClubs("clubs", "ace");
    vector<Card> hand = {cardHearts, cardClubs};

    EXPECT_CALL(mock, callGetCardTrueValue(_))
    .Times(2);

    bool actual = playGame.handis21(&mock, hand);
    EXPECT_EQ(actual, false);    
}

TEST(GameLogic_Handis21Should, ReturnTrueWhenHandIs21WithMultipleAces) {
    MockGame mock;
    PlayGame playGame;
    Card cardHearts("hearts", "ace");
    Card cardClubs("clubs", "ace");
    Card cardSpades("spades", "nine");
    vector<Card> hand = {cardHearts, cardClubs, cardSpades};

    EXPECT_CALL(mock, callGetCardTrueValue(_))
    .Times(3)
    .WillOnce(Return(11))
    .WillOnce(Return(1))
    .WillOnce(Return(9));

    bool actual = playGame.handis21(&mock, hand, 11);
    EXPECT_EQ(actual, true);    
}

TEST(GameLogic_Handis21Should, ReturnTrueWhenHandIs21WithAceAsOne) {
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

    bool actual = playGame.handis21(&mock, hand, 1);
    EXPECT_EQ(actual, true);    
}

TEST(GameLogic_Handis21Should, ReturnTrueWhenHandIs21WithoutAce) {
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

    bool actual = playGame.handis21(&mock, hand);
    EXPECT_EQ(actual, true);    
}


TEST(GameLogic_ReturnListOfPlayersAt21Should, ReturnPopulatedArrayOfSizeOneIfOnePlayerHasWon){
    MockGame mock;

    PlayGame playGame;
    Player* player = new Player();
    Player* player2 = new Player();
    vector<Player*> players = {player, player2};
    playGame.setPlayerList(players);

    EXPECT_CALL(mock, callVerifyHandis21(_, _))
    .Times(2)
    .WillOnce(Return(true))
    .WillOnce(Return(false));

    vector<int> actual = playGame.returnListOfPlayersAt21(&mock);

    EXPECT_EQ(actual.size(), 1);    
}

TEST(GameLogic_ReturnListOfPlayersAt21Should, ReturnPopulatedArrayOfSizeTwoIfTwoPlayersHaveWon){
    MockGame mock;

    PlayGame playGame;
    Player* player = new Player();
    Player* player2 = new Player();
    vector<Player*> players = {player, player2};
    playGame.setPlayerList(players);

    EXPECT_CALL(mock, callVerifyHandis21(_, _))
    .Times(2)
    .WillOnce(Return(true))
    .WillOnce(Return(true));

    vector<int> actual = playGame.returnListOfPlayersAt21(&mock);

    EXPECT_EQ(actual.size(), 2);    
}

TEST(GameLogic_ReturnListOfPlayersAt21Should, ReturnArrayWithValueOfOneIfSecondPlayerHasWon){
    MockGame mock;

    PlayGame playGame;
    Player* player = new Player();
    Player* player2 = new Player();
    vector<Player*> players = {player, player2};
    playGame.setPlayerList(players);

    EXPECT_CALL(mock, callVerifyHandis21(_, _))
    .Times(2)
    .WillOnce(Return(false))
    .WillOnce(Return(true));

    vector<int> actual = playGame.returnListOfPlayersAt21(&mock);

    EXPECT_EQ(actual.back(), 1);    
}

TEST(GameLogic_ReturnListOfPlayersAt21Should, ReturnUnpopulatedArrayIfNoPlayersHaveWon){
    MockGame mock;

    PlayGame playGame;
    Player* player = new Player();
    Player* player2 = new Player();
    vector<Player*> players = {player, player2};
    playGame.setPlayerList(players);

    EXPECT_CALL(mock, callVerifyHandis21(_, _))
    .Times(2)
    .WillOnce(Return(false))
    .WillOnce(Return(false));

    vector<int> actual = playGame.returnListOfPlayersAt21(&mock);

    EXPECT_EQ(actual.size(),0);    
}


TEST(GameLogic_HandHasGoneBustShould, ReturnFalseWhenUnder21) {
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

    bool actual = playGame.handHasGoneBust(&mock, hand);

    EXPECT_EQ(actual, false);
}

TEST(GameLogic_HandHasGoneBustShould, ReturnTrueWhenOver21) {
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

    bool actual = playGame.handHasGoneBust(&mock, hand);

    EXPECT_EQ(actual, true);
}

TEST(GameLogic_HandHasGoneBustShould, ReturnFalseWhenExactly21) {
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

    bool actual = playGame.handHasGoneBust(&mock, hand);

    EXPECT_EQ(actual, false);
}


TEST(GameLogic_AllPlayersHaveGoneBustShould, ReturnFalseWhenOnePlayerIsntBust) {
    MockGame mock;
    PlayGame playGame;   
    Player* player = new Player();
    Player* player2 = new Player();
    vector<Player*> players = {player, player2};
    playGame.setPlayerList(players);
    vector<Card> hand = {};

    EXPECT_CALL(mock, callHandHasGoneBust(_, _))
    .Times(2)
    .WillOnce(Return(true))
    .WillOnce(Return(false));

    bool actual = playGame.allPlayersHaveGoneBust(&mock);

    EXPECT_EQ(actual, false);
}

TEST(GameLogic_AllPlayersHaveGoneBustShould, ReturnFalseOnFirstTryWhenAllPlayersAreBust) {
    MockGame mock;
    PlayGame playGame;   
    Player* player = new Player();
    Player* player2 = new Player();
    vector<Player*> players = {player, player2};
    playGame.setPlayerList(players);
    vector<Card> hand = {};

    EXPECT_CALL(mock, callHandHasGoneBust(_, _))
    .Times(1)
    .WillOnce(Return(false));

    bool actual = playGame.allPlayersHaveGoneBust(&mock);

    EXPECT_EQ(actual, false);
}

TEST(GameLogic_AllPlayersHaveGoneBustShould, ReturnTrueWhenAllPlayersAreBust) {
    MockGame mock;
    PlayGame playGame;   
    Player* player = new Player();
    Player* player2 = new Player();
    vector<Player*> players = {player, player2};
    playGame.setPlayerList(players);
    vector<Card> hand = {};

    EXPECT_CALL(mock, callHandHasGoneBust(_, _))
    .Times(2)
    .WillRepeatedly(Return(true));

    bool actual = playGame.allPlayersHaveGoneBust(&mock);

    EXPECT_EQ(actual, true);
}