#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "game/playgame.h"
#include "wrapper.h"
#include <vector>
#include <sstream>

using namespace std;
using ::testing::Return;
using ::testing::_;

TEST(DetermineWinnerFromNobody21Should, PrintCorrectTextGivenDealerAsWinnerGivenNoPlayers) {
    MockGame mock;

    stringstream buffer;
    streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf());
    PlayGame playGame;
    Player* dealer = new Player();
    playGame.setDealer(dealer);

    vector<int> populatedVector = {};
    pair<int, vector<int>> highest = make_pair(0, populatedVector);

    EXPECT_CALL(mock, callGetListOfPlayersWithHighestScores(_))
    .Times(1)
    .WillOnce(Return(highest));

    EXPECT_CALL(mock, callGetCurrentTotal(_))
    .Times(1)
    .WillOnce(Return(12));

    EXPECT_CALL(mock, callDisplayWin(_, _, _))
    .Times(1)
    .WillOnce([](bool dealerHasWon, vector<int> playersWhoHaveWon, int score) {
        cout << "The dealer value is " << dealerHasWon << " and the playersWhoHaveWon size is "<< playersWhoHaveWon.size();
    });

    playGame.determineWinnerFromNobody21(&mock);

    string text = buffer.str();
    cout.rdbuf(prevcoutbuf);


    EXPECT_EQ("The dealer value is 1 and the playersWhoHaveWon size is 0", text);
}

TEST(DetermineWinnerFromNobody21Should, PrintCorrectTextGivenDealerAsWinnerGivenOnePlayerWithLesserScore) {
    MockGame mock;

    stringstream buffer;
    streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf());
    PlayGame playGame;
    Player* dealer = new Player();
    playGame.setDealer(dealer);

    vector<int> populatedVector = {1};
    pair<int, vector<int>> highest = make_pair(1, populatedVector);

    EXPECT_CALL(mock, callGetListOfPlayersWithHighestScores(_))
    .Times(1)
    .WillOnce(Return(highest));

    EXPECT_CALL(mock, callGetCurrentTotal(_))
    .Times(1)
    .WillOnce(Return(12));

    EXPECT_CALL(mock, callDisplayWin(_, _, _))
    .Times(1)
    .WillOnce([](bool dealerHasWon, vector<int> playersWhoHaveWon, int score) {
        cout << "The dealer value is " << dealerHasWon << " and the playersWhoHaveWon size is "<< playersWhoHaveWon.size();
    });

    playGame.determineWinnerFromNobody21(&mock);

    string text = buffer.str();
    cout.rdbuf(prevcoutbuf);


    EXPECT_EQ("The dealer value is 1 and the playersWhoHaveWon size is 0", text);
}

TEST(DetermineWinnerFromNobody21Should, PrintCorrectTextGivenPlayerOneAsWinnerGivenPlayerHasHigherScore) {
    MockGame mock;

    stringstream buffer;
    streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf());
    PlayGame playGame;
    Player* dealer = new Player();
    playGame.setDealer(dealer);

    vector<int> populatedVector = {1};
    pair<int, vector<int>> highest = make_pair(21, populatedVector);

    EXPECT_CALL(mock, callGetListOfPlayersWithHighestScores(_))
    .Times(1)
    .WillOnce(Return(highest));

    EXPECT_CALL(mock, callGetCurrentTotal(_))
    .Times(2)
    .WillRepeatedly(Return(1));

    EXPECT_CALL(mock, callDisplayWin(_, _, _))
    .Times(1)
    .WillOnce([](bool dealerHasWon, vector<int> playersWhoHaveWon, int score) {
        cout << "The dealer value is " << dealerHasWon << " and the playersWhoHaveWon size is "<< playersWhoHaveWon.size();
    });

    playGame.determineWinnerFromNobody21(&mock);

    string text = buffer.str();
    cout.rdbuf(prevcoutbuf);


    EXPECT_EQ("The dealer value is 0 and the playersWhoHaveWon size is 1", text);
}

TEST(DetermineWinnerFromNobody21Should, PrintCorrectTextGivenPlayerOneAndTwoAsWinnersGivenPlayersHaveHighestScores) {
    MockGame mock;

    stringstream buffer;
    streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf());
    PlayGame playGame;
    Player* dealer = new Player();
    playGame.setDealer(dealer);

    vector<int> populatedVector = {1, 1};
    pair<int, vector<int>> highest = make_pair(21, populatedVector);

    EXPECT_CALL(mock, callGetListOfPlayersWithHighestScores(_))
    .Times(1)
    .WillOnce(Return(highest));

    EXPECT_CALL(mock, callGetCurrentTotal(_))
    .Times(2)
    .WillRepeatedly(Return(1));

    EXPECT_CALL(mock, callDisplayWin(_, _, _))
    .Times(1)
    .WillOnce([](bool dealerHasWon, vector<int> playersWhoHaveWon, int score) {
        cout << "The dealer value is " << dealerHasWon << " and the playersWhoHaveWon size is "<< playersWhoHaveWon.size();
    });

    playGame.determineWinnerFromNobody21(&mock);

    string text = buffer.str();
    cout.rdbuf(prevcoutbuf);


    EXPECT_EQ("The dealer value is 0 and the playersWhoHaveWon size is 2", text);
}

TEST(DetermineWinnerFromNobody21Should, PrintCorrectTextGivenPlayerOneAndTwoandDealerAsWinnersGivenPlayersHaveHighestScores) {
    MockGame mock;

    stringstream buffer;
    streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf());
    PlayGame playGame;
    Player* dealer = new Player();
    playGame.setDealer(dealer);

    vector<int> populatedVector = {1, 1};
    pair<int, vector<int>> highest = make_pair(21, populatedVector);

    EXPECT_CALL(mock, callGetListOfPlayersWithHighestScores(_))
    .Times(1)
    .WillOnce(Return(highest));

    EXPECT_CALL(mock, callGetCurrentTotal(_))
    .Times(2)
    .WillRepeatedly(Return(highest.first));

    EXPECT_CALL(mock, callDisplayWin(_, _, _))
    .Times(1)
    .WillOnce([](bool dealerHasWon, vector<int> playersWhoHaveWon, int score) {
        cout << "The dealer value is " << dealerHasWon << " and the playersWhoHaveWon size is "<< playersWhoHaveWon.size();
    });

    playGame.determineWinnerFromNobody21(&mock);

    string text = buffer.str();
    cout.rdbuf(prevcoutbuf);


    EXPECT_EQ("The dealer value is 1 and the playersWhoHaveWon size is 2", text);
}


TEST(DisplayWin, PrintDealerWonToOutputOnDealerWinning) {
    stringstream buffer;
    streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf());
    PlayGame playGame;
    vector<int> emptyVector;
    playGame.displayWin(true, emptyVector, 0);
    string text = buffer.str();
    cout.rdbuf(prevcoutbuf);
    EXPECT_EQ("Dealer has won with a score of 0\n", text);
}

TEST(DisplayWin, PrintPlayerOneHasWonAndDealerHasWonToOutputOnDealerAndPlayerOneTying) {
    stringstream buffer;
    streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf());
    PlayGame playGame;
    vector<int> playerOneWon = {0};
    playGame.displayWin(true, playerOneWon, 21);
    string text = buffer.str();
    cout.rdbuf(prevcoutbuf);
    EXPECT_EQ("We have a tie!\nPlayer 1 has won with a score of: 21\n\nAnd Dealer has also achieved 21\n\n", text);
}

TEST(DisplayWin, PrintPlayerOneHasWonOutput) {
    stringstream buffer;
    streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf());
    PlayGame playGame;
    vector<int> playerOneWon = {0};
    playGame.displayWin(false, playerOneWon, 21);
    string text = buffer.str();
    cout.rdbuf(prevcoutbuf);
    EXPECT_EQ("Player 1 has won and with a score of 21\n\n", text);
}


TEST(setHighestValidHandValueForPlayerShould, OnlyCallGetTotalOnceWhenWeHaveNoAce) {
    MockGame mock;
    PlayGame playGame;
    Player* player = new Player();

    EXPECT_CALL(mock, callCheckIfHandHasAce(_))
    .Times(1)
    .WillOnce(Return(false));

    EXPECT_CALL(mock, callGetTotalHand(_, _))
    .Times(1)
    .WillOnce(Return(20));

    playGame.setHighestValidHandValueForPlayer(&mock, player);

    EXPECT_EQ(player->getCurrentTotal(), 20);
}

TEST(setHighestValidHandValueForPlayerShould, ReturnLessOfTwoValuesWhenAce11CountIsMoreThan21) {
    MockGame mock;
    PlayGame playGame;
    Player* player = new Player();

    EXPECT_CALL(mock, callCheckIfHandHasAce(_))
    .Times(1)
    .WillOnce(Return(true));

    EXPECT_CALL(mock, callGetTotalHand(_, _, _))
    .Times(2)
    .WillOnce(Return(22))
    .WillOnce(Return(1));

    playGame.setHighestValidHandValueForPlayer(&mock, player);

    EXPECT_EQ(player->getCurrentTotal(), 1);
}

TEST(setHighestValidHandValueForPlayerShould, ReturnHigherOfTwoValuesWhenAce11CountIsLessThan21) {
    MockGame mock;
    PlayGame playGame;
    Player* player = new Player();

    EXPECT_CALL(mock, callCheckIfHandHasAce(_))
    .Times(1)
    .WillOnce(Return(true));

    EXPECT_CALL(mock, callGetTotalHand(_, _, _))
    .Times(2)
    .WillOnce(Return(11))
    .WillOnce(Return(1));

    playGame.setHighestValidHandValueForPlayer(&mock, player);

    EXPECT_EQ(player->getCurrentTotal(), 11);
}



TEST(GetListOfPlayersWithHighestScoresShould, ReturnOnePlayerWhenOnlyOnePlayerHasTheHighestScore) {
    MockGame mock;
    PlayGame playGame;
    Player* player = new Player();
    Player* player2 = new Player();

    vector<Player*> players = {player, player2};
    playGame.setPlayerList(players);

    EXPECT_CALL(mock, callGetCurrentTotal(_))
    .Times(2)
    .WillOnce(Return(1))
    .WillOnce(Return(2));

    pair<int, vector<int>> actual = playGame.getListOfPlayersWithHighestScores(&mock);

    EXPECT_EQ(actual.second.size(), 1);
}

TEST(GetListOfPlayersWithHighestScoresShould, ReturnOnePlayersValueWhenOnlyOnePlayerHasTheHighestScore) {
    MockGame mock;
    PlayGame playGame;
    Player* player = new Player();
    Player* player2 = new Player();

    vector<Player*> players = {player, player2};
    playGame.setPlayerList(players);

    EXPECT_CALL(mock, callGetCurrentTotal(_))
    .Times(2)
    .WillOnce(Return(1))
    .WillOnce(Return(2));

    pair<int, vector<int>> actual = playGame.getListOfPlayersWithHighestScores(&mock);

    EXPECT_EQ(actual.first, 2);
}

TEST(GetListOfPlayersWithHighestScoresShould, ReturnTwoPlayersWhenBothHaveHighest) {
    MockGame mock;
    PlayGame playGame;
    Player* player = new Player();
    Player* player2 = new Player();

    vector<Player*> players = {player, player2};
    playGame.setPlayerList(players);


    EXPECT_CALL(mock, callGetCurrentTotal(_))
    .Times(2)
    .WillRepeatedly(Return(12));

    pair<int, vector<int>> actual = playGame.getListOfPlayersWithHighestScores(&mock);

    EXPECT_EQ(actual.second.size(), 2);
}