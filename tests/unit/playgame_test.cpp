#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "game/playgame.h"
#include "wrapper.h"

using namespace std;
using ::testing::Return;
using ::testing::_;

TEST(PlayGame_RegularGamePlayShould, ReturnTrueIfDealerHasGoneBustWhenDealersHandHasGoneBust) {
    MockGame mock;
    PlayGame playGame;

    EXPECT_CALL(mock, callCheckIfHandHasGoneBust(_, _))
    .Times(1)
    .WillOnce(Return(true));

    bool actual = playGame.regularGamePlay(&mock);
    EXPECT_EQ(actual, true);
}

TEST(PlayGame_RegularGamePlayShould, PrintDealerHasGoneBustWhenDealersHandHasGoneBust) {
    MockGame mock;
    PlayGame playGame;

    stringstream buffer;
    streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf());

    EXPECT_CALL(mock, callCheckIfHandHasGoneBust(_, _))
    .Times(1)
    .WillOnce(Return(true));
    
    bool actual = playGame.regularGamePlay(&mock);

    string text = buffer.str();
    cout.rdbuf(prevcoutbuf);
    
    EXPECT_EQ(text, "\tDealer has Dealer has gone bust! Everyone else has won!!\n\n");
}

TEST(PlayGame_RegularGamePlayShould, ReturnTrueIfAPlayerHasAchieved21) {
    MockGame mock;
    PlayGame playGame;

    vector<int> vectorPlayersAchieved21 = {1, 5};

    EXPECT_CALL(mock, callCheckIfHandHasGoneBust(_, _))
    .Times(1)
    .WillOnce(Return(false));

    EXPECT_CALL(mock, callReturnListOfPlayersAt21(_))
    .Times(2)
    .WillRepeatedly(Return(vectorPlayersAchieved21));

    bool actual = playGame.regularGamePlay(&mock);
    EXPECT_EQ(actual, true);
}

TEST(PlayGame_RegularGamePlayShould, PrintSetTestStringIfAPlayerHasAchieved21) {
    MockGame mock;
    PlayGame playGame;

    stringstream buffer;
    streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf());

    vector<int> vectorPlayersAchieved21 = {1, 5};

    EXPECT_CALL(mock, callCheckIfHandHasGoneBust(_, _))
    .Times(1)
    .WillOnce(Return(false));

    EXPECT_CALL(mock, callReturnListOfPlayersAt21(_))
    .Times(2)
    .WillRepeatedly(Return(vectorPlayersAchieved21));

    EXPECT_CALL(mock, callDisplayWin(_, _, _))
    .Times(1)
    .WillRepeatedly([](){
        cout <<"Example message for player over 21";
    });

    bool actual = playGame.regularGamePlay(&mock);

    string text = buffer.str();
    cout.rdbuf(prevcoutbuf);

    EXPECT_EQ(text, "\tDealer has Example message for player over 21");
}

TEST(PlayGame_RegularGamePlayShould, ReturnTrueIfDealerGoesOver17) {
    MockGame mock;
    PlayGame playGame;

    vector<int> vectorPlayersAchieved21 = {};

    EXPECT_CALL(mock, callCheckIfHandHasGoneBust(_, _))
    .Times(1)
    .WillOnce(Return(false));

    EXPECT_CALL(mock, callReturnListOfPlayersAt21(_))
    .Times(1)
    .WillOnce(Return(vectorPlayersAchieved21));

    EXPECT_CALL(mock, callGetCurrentTotal(_))
    .Times(1)
    .WillOnce(Return(18));

    bool actual = playGame.regularGamePlay(&mock);
    EXPECT_EQ(actual, true);
}

TEST(PlayGame_RegularGamePlayShould, PrintSetTestStringIfADealerGoesOver17) {
    MockGame mock;
    PlayGame playGame;

    stringstream buffer;
    streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf());

    vector<int> vectorPlayersAchieved21 = {};

    EXPECT_CALL(mock, callCheckIfHandHasGoneBust(_, _))
    .Times(1)
    .WillOnce(Return(false));

    EXPECT_CALL(mock, callReturnListOfPlayersAt21(_))
    .Times(1)
    .WillOnce(Return(vectorPlayersAchieved21));

    EXPECT_CALL(mock, callGetCurrentTotal(_))
    .Times(1)
    .WillOnce(Return(18));

    EXPECT_CALL(mock, callDetermineWinnerFromNobody21(_))
    .Times(1)
    .WillOnce([](){
        cout <<"Example message for dealer over 17";
    });

    bool actual = playGame.regularGamePlay(&mock);

    string text = buffer.str();
    cout.rdbuf(prevcoutbuf);

    EXPECT_EQ(text, "\tDealer has Example message for dealer over 17");
}

TEST(PlayGame_RegularGamePlayShould, ReturnTrueIfAllPlayersBustButTheDealer) {
    MockGame mock;
    PlayGame playGame;

    vector<int> vectorPlayersAchieved21 = {};

    EXPECT_CALL(mock, callCheckIfHandHasGoneBust(_, _))
    .Times(1)
    .WillOnce(Return(false));

    EXPECT_CALL(mock, callReturnListOfPlayersAt21(_))
    .Times(1)
    .WillOnce(Return(vectorPlayersAchieved21));

    EXPECT_CALL(mock, callGetCurrentTotal(_))
    .Times(1)
    .WillOnce(Return(14));

    EXPECT_CALL(mock, callCheckIfAllPlayersHaveGoneBust(_))
    .Times(1)
    .WillOnce(Return(true));

    bool actual = playGame.regularGamePlay(&mock);

    EXPECT_EQ(actual, true);
}

TEST(PlayGame_RegularGamePlayShould, PrintSetTestStringIfAllPlayersBustButTheDealer) {
    MockGame mock;
    PlayGame playGame;

    stringstream buffer;
    streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf());

    vector<int> vectorPlayersAchieved21 = {};

    EXPECT_CALL(mock, callCheckIfHandHasGoneBust(_, _))
    .Times(1)
    .WillOnce(Return(false));

    EXPECT_CALL(mock, callReturnListOfPlayersAt21(_))
    .Times(1)
    .WillOnce(Return(vectorPlayersAchieved21));

    EXPECT_CALL(mock, callGetCurrentTotal(_))
    .Times(1)
    .WillOnce(Return(14));

    EXPECT_CALL(mock, callCheckIfAllPlayersHaveGoneBust(_))
    .Times(1)
    .WillOnce(Return(true));

    bool actual = playGame.regularGamePlay(&mock);

    string text = buffer.str();
    cout.rdbuf(prevcoutbuf);

    EXPECT_EQ(text, "\tDealer has All players but the dealer have gone bust. Game over.\n\n");
}

TEST(PlayGame_RegularGamePlayShould, ReturnFalseIfNoConditionsAreMet) {
    MockGame mock;
    PlayGame playGame;

    vector<int> vectorPlayersAchieved21 = {};

    EXPECT_CALL(mock, callCheckIfHandHasGoneBust(_, _))
    .Times(1)
    .WillOnce(Return(false));

    EXPECT_CALL(mock, callReturnListOfPlayersAt21(_))
    .Times(1)
    .WillOnce(Return(vectorPlayersAchieved21));

    EXPECT_CALL(mock, callGetCurrentTotal(_))
    .Times(1)
    .WillOnce(Return(11));

    EXPECT_CALL(mock, callCheckIfAllPlayersHaveGoneBust(_))
    .Times(1)
    .WillOnce(Return(false));

    bool actual = playGame.regularGamePlay(&mock);
    EXPECT_EQ(actual, false);
}

TEST(PlayGame_RegularGamePlayShould, PrintSetTestStringIfNoConditionsAreMet) {
    MockGame mock;
    PlayGame playGame;

    stringstream buffer;
    streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf());

    vector<int> vectorPlayersAchieved21 = {};

    EXPECT_CALL(mock, callCheckIfHandHasGoneBust(_, _))
    .Times(1)
    .WillOnce(Return(false));

    EXPECT_CALL(mock, callReturnListOfPlayersAt21(_))
    .Times(1)
    .WillOnce(Return(vectorPlayersAchieved21));

    EXPECT_CALL(mock, callGetCurrentTotal(_))
    .Times(1)
    .WillOnce(Return(11));

    EXPECT_CALL(mock, callCheckIfAllPlayersHaveGoneBust(_))
    .Times(1)
    .WillOnce(Return(false));

    bool actual = playGame.regularGamePlay(&mock);

    string text = buffer.str();
    cout.rdbuf(prevcoutbuf);

    EXPECT_EQ(text, "\tDealer has Nobody has won this round\n\t\tThe Dealer has placed their next card face-down.\n\n");
}


TEST(PlayGame_InitialiseGameShould, PrintCorrectText) {
    MockGame mock;
    PlayGame playGame;

    stringstream buffer;
    streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf());
    Card card("hearts", "two");
    vector<Card> hand = {card};

    EXPECT_CALL(mock, callGetHand(_))
    .Times(2)
    .WillRepeatedly(Return(hand));

    playGame.initialiseGame(&mock);

    string text = buffer.str();
    cout.rdbuf(prevcoutbuf);
    EXPECT_EQ(text, "\tThe Dealer has a two of hearts\n\n\t\tThe Dealer has placed their second card face-down.\n\n");
}


TEST(PlayGame_PlayGameShould, PrintTheCorrectTextGivenDealerHasWonIsTrue) {
    MockGame mock;
    PlayGame playGame;
    Player* dealer = new Player();
    Card card("hearts", "two");
    vector<Card> hand = {card};
    
    stringstream buffer;
    streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf());

    vector<int> noPlayersHaveWon = {};

    EXPECT_CALL(mock, callReturnListOfPlayersAt21(_))
    .Times(1)
    .WillOnce(Return(noPlayersHaveWon));
    
    EXPECT_CALL(mock, callVerifyHandHasWon(_, _))
    .Times(1)
    .WillOnce(Return(true));

    EXPECT_CALL(mock, callGetHand(_))
    .Times(3)
    .WillRepeatedly(Return(hand));

    playGame.playGame(&mock);

    string text = buffer.str();
    cout.rdbuf(prevcoutbuf);

    EXPECT_EQ(text, "Dealers second card is: two of hearts\n\n");
}

TEST(PlayGame_PlayGameShould, PrintTheCorrectTextGivenAPlayerHasWon) {
    MockGame mock;
    PlayGame playGame;
    Player* dealer = new Player();
    Card card("hearts", "two");
    vector<Card> hand = {card};
    
    stringstream buffer;
    streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf());

    vector<int> playersHaveWon = {1};

    EXPECT_CALL(mock, callReturnListOfPlayersAt21(_))
    .Times(1)
    .WillOnce(Return(playersHaveWon));
    
    EXPECT_CALL(mock, callVerifyHandHasWon(_, _))
    .Times(1)
    .WillOnce(Return(false));

    EXPECT_CALL(mock, callGetHand(_))
    .Times(3)
    .WillRepeatedly(Return(hand));

    playGame.playGame(&mock);

    string text = buffer.str();
    cout.rdbuf(prevcoutbuf);

    EXPECT_EQ(text, "Dealers second card is: two of hearts\n\n");
}

TEST(PlayGame_PlayGameShould, PrintTheCorrectTextGivenNobodyHasWonTheInitialRound) {
    MockGame mock;
    PlayGame playGame;
    Player* dealer = new Player();
    Card card("hearts", "two");
    vector<Card> hand = {card};
    
    stringstream buffer;
    streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf());

    vector<int> noPlayersHaveWon = {};
    EXPECT_CALL(mock, callReturnListOfPlayersAt21(_))
    .Times(1)
    .WillOnce(Return(noPlayersHaveWon));
    
    EXPECT_CALL(mock, callVerifyHandHasWon(_, _))
    .Times(1)
    .WillOnce(Return(false));

    EXPECT_CALL(mock, callGetHand(_))
    .Times(1)
    .WillOnce(Return(hand));

    EXPECT_CALL(mock, callRegularGamePlay(_))
    .Times(1)
    .WillRepeatedly(Return(true));

    playGame.playGame(&mock);

    string text = buffer.str();
    cout.rdbuf(prevcoutbuf);

    EXPECT_EQ(text, "Next round has started\n\n");
}