#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "game/playgame.h"
#include "wrapper.h"
#include <vector>
#include <sstream>

using namespace std;
using ::testing::Return;
using ::testing::_;

TEST(WinnerHandler_DetermineWinnerFromNobody21Should, PrintCorrectTextGivenDealerAsOnlyWinner) {
    MockGame mock;

    stringstream buffer;
    streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf());
    PlayGame playGame;

    vector<int> populatedVector = {};
    pair<int, vector<int>> highest = make_pair(0, populatedVector);

    EXPECT_CALL(mock, callGetListOfPlayersWithHighestScores(_))
    .Times(1)
    .WillOnce(Return(highest));

    EXPECT_CALL(mock, callGetCurrentTotal(_))
    .Times(1)
    .WillOnce(Return(1));

    EXPECT_CALL(mock, callDisplayWin(true, _, 1))
    .Times(1)
    .WillOnce([](bool dealerHasWon, vector<int> players, int score) {
        cout << "The dealer value is true";
    });

    playGame.determineWinnerFromNobody21(&mock);

    string text = buffer.str();
    cout.rdbuf(prevcoutbuf);


    EXPECT_EQ("The dealer value is true", text);
}

TEST(WinnerHandler_DetermineWinnerFromNobody21Should, PrintCorrectTextGivenDealerAsWinnerGivenOnePlayerWithLesserScore) {
    MockGame mock;

    stringstream buffer;
    streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf());
    PlayGame playGame;

    vector<int> populatedVector = {1};
    pair<int, vector<int>> highest = make_pair(1, populatedVector);

    EXPECT_CALL(mock, callGetListOfPlayersWithHighestScores(_))
    .Times(1)
    .WillOnce(Return(highest));

    EXPECT_CALL(mock, callGetCurrentTotal(_))
    .Times(1)
    .WillOnce(Return(12));

    EXPECT_CALL(mock, callDisplayWin(true, _, 12))
    .Times(1)
    .WillOnce([](bool dealerHasWon, vector<int> playersWhoHaveWon, int score) {
        cout << "The dealer value is " << dealerHasWon << " and the playersWhoHaveWon size is "<< playersWhoHaveWon.size();
    });

    playGame.determineWinnerFromNobody21(&mock);

    string text = buffer.str();
    cout.rdbuf(prevcoutbuf);


    EXPECT_EQ("The dealer value is 1 and the playersWhoHaveWon size is 0", text);
}

TEST(WinnerHandler_DetermineWinnerFromNobody21Should, PrintCorrectTextGivenPlayerOneAsWinnerGivenPlayerHasHigherScore) {
    MockGame mock;

    stringstream buffer;
    streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf());
    PlayGame playGame;

    vector<int> populatedVector = {1};
    pair<int, vector<int>> highest = make_pair(21, populatedVector);

    EXPECT_CALL(mock, callGetListOfPlayersWithHighestScores(_))
    .Times(1)
    .WillOnce(Return(highest));

    EXPECT_CALL(mock, callGetCurrentTotal(_))
    .Times(1)
    .WillOnce(Return(1));

    EXPECT_CALL(mock, callDisplayWin(false, _, 21))
    .Times(1)
    .WillOnce([](bool dealerHasWon, vector<int> playersWhoHaveWon, int score) {
        cout << "The dealer value is " << dealerHasWon << " and the playersWhoHaveWon size is "<< playersWhoHaveWon.size();
    });

    playGame.determineWinnerFromNobody21(&mock);

    string text = buffer.str();
    cout.rdbuf(prevcoutbuf);


    EXPECT_EQ("The dealer value is 0 and the playersWhoHaveWon size is 1", text);
}

TEST(WinnerHandler_DetermineWinnerFromNobody21Should, PrintCorrectTextGivenPlayerOneAndTwoAsWinnersGivenPlayersHaveHighestScores) {
    MockGame mock;

    stringstream buffer;
    streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf());
    PlayGame playGame;

    vector<int> populatedVector = {1, 1};
    pair<int, vector<int>> highest = make_pair(21, populatedVector);

    EXPECT_CALL(mock, callGetListOfPlayersWithHighestScores(_))
    .Times(1)
    .WillOnce(Return(highest));

    EXPECT_CALL(mock, callGetCurrentTotal(_))
    .Times(1)
    .WillOnce(Return(1));

    EXPECT_CALL(mock, callDisplayWin(false, _, 21))
    .Times(1)
    .WillOnce([](bool dealerHasWon, vector<int> playersWhoHaveWon, int score) {
        cout << "The dealer value is " << dealerHasWon << " and the playersWhoHaveWon size is "<< playersWhoHaveWon.size();
    });

    playGame.determineWinnerFromNobody21(&mock);

    string text = buffer.str();
    cout.rdbuf(prevcoutbuf);


    EXPECT_EQ("The dealer value is 0 and the playersWhoHaveWon size is 2", text);
}

TEST(WinnerHandler_DetermineWinnerFromNobody21Should, PrintCorrectTextGivenPlayerOneAndTwoandDealerAsWinnersGivenPlayersHaveHighestScores) {
    MockGame mock;

    stringstream buffer;
    streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf());
    PlayGame playGame;

    vector<int> populatedVector = {1, 1};
    pair<int, vector<int>> highest = make_pair(21, populatedVector);

    EXPECT_CALL(mock, callGetListOfPlayersWithHighestScores(_))
    .Times(1)
    .WillOnce(Return(highest));

    EXPECT_CALL(mock, callGetCurrentTotal(_))
    .Times(1)
    .WillOnce(Return(highest.first));

    EXPECT_CALL(mock, callDisplayWin(true, _, 21))
    .Times(1)
    .WillOnce([](bool dealerHasWon, vector<int> playersWhoHaveWon, int score) {
        cout << "The dealer value is " << dealerHasWon << " and the playersWhoHaveWon size is "<< playersWhoHaveWon.size();
    });

    playGame.determineWinnerFromNobody21(&mock);

    string text = buffer.str();
    cout.rdbuf(prevcoutbuf);


    EXPECT_EQ("The dealer value is 1 and the playersWhoHaveWon size is 2", text);
}

TEST(WinnerHandler_DisplayWin, PrintPlayerOneHasWonAndDealerHasWonToOutputOnDealerAndPlayerOneTying) {
    stringstream buffer;
    streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf());
    PlayGame playGame;
    vector<int> playerOneWon = {0};
    playGame.displayWin(true, playerOneWon, 21);
    string text = buffer.str();
    cout.rdbuf(prevcoutbuf);
    EXPECT_EQ("We have a tie!\nPlayer 1 has won with a score of: 21\n\nAnd Dealer has also achieved 21\n\n", text);
}

TEST(WinnerHandler_DisplayWin, PrintPlayerListOfWonPlayersGivenMultipleWinnersAndDealerNotTying) {
    stringstream buffer;
    streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf());
    PlayGame playGame;
    vector<int> playerOneWon = {0, 1};
    playGame.displayWin(false, playerOneWon, 21);
    string text = buffer.str();
    cout.rdbuf(prevcoutbuf);
    EXPECT_EQ("We have a tie!\nPlayer 1 has won with a score of: 21\n\nPlayer 2 has won with a score of: 21\n\n", text);
}   

TEST(WinnerHandler_DisplayWin, PrintDealerWonToOutputOnDealerWinning) {
    stringstream buffer;
    streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf());
    PlayGame playGame;
    vector<int> emptyVector;
    playGame.displayWin(true, emptyVector, 0);
    string text = buffer.str();
    cout.rdbuf(prevcoutbuf);
    EXPECT_EQ("Dealer has won with a score of 0\n", text);
}

TEST(WinnerHandler_DisplayWin, PrintPlayerOneHasWonOutput) {
    stringstream buffer;
    streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf());
    PlayGame playGame;
    vector<int> playerOneWon = {0};
    playGame.displayWin(false, playerOneWon, 21);
    string text = buffer.str();
    cout.rdbuf(prevcoutbuf);
    EXPECT_EQ("Player 1 has won and with a score of 21\n\n", text);
}   


TEST(WinnerHandler_SetHighestValidHandValueForPlayerShould, SetThePlayersCurrentTotalToTheHighestValueGivenNoAce) {
    MockGame mock;
    PlayGame playGame;
    Player* player = new Player();

    EXPECT_CALL(mock, callCheckIfHandHasAce(_))
    .Times(1)
    .WillOnce(Return(false));

    EXPECT_CALL(mock, callGetTotalHand(_, _))
    .Times(1)
    .WillOnce(Return(20));

    playGame.setHighestValidHandValueForPlayer(&mock, player, false);

    EXPECT_EQ(player->getCurrentTotal(), 20);
}

TEST(WinnerHandler_SetHighestValidHandValueForPlayerShould, ReturnLessOfTwoValuesWhenAce11CountIsMoreThan21) {
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

    playGame.setHighestValidHandValueForPlayer(&mock, player, false);

    EXPECT_EQ(player->getCurrentTotal(), 1);
}

TEST(WinnerHandler_SetHighestValidHandValueForPlayerShould, ReturnHigherOfTwoValuesWhenAce11CountIsLessThan21) {
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

    playGame.setHighestValidHandValueForPlayer(&mock, player, false);

    EXPECT_EQ(player->getCurrentTotal(), 11);
}

TEST(WinnerHandler_SetHighestValidHandValueForPlayerShould, SetScoreOver21ForHandWithAceDealerIsSetToTrue) {
    MockGame mock;
    PlayGame playGame;
    Player* dealer = new Player();

    EXPECT_CALL(mock, callCheckIfHandHasAce(_))
    .Times(1)
    .WillOnce(Return(true));

    EXPECT_CALL(mock, callGetTotalHand(_, _, _))
    .Times(2)
    .WillOnce(Return(23))
    .WillOnce(Return(10));

    playGame.setHighestValidHandValueForPlayer(&mock, dealer, true);

    EXPECT_EQ(dealer->getCurrentTotal(), 23);
}

TEST(WinnerHandler_SetHighestValidHandValueForPlayerShould, SetScoreOver21ForHandWithoutAceDealerIsSetToTrue) {
    MockGame mock;
    PlayGame playGame;
    Player* dealer = new Player();

    EXPECT_CALL(mock, callCheckIfHandHasAce(_))
    .Times(1)
    .WillOnce(Return(false));

    EXPECT_CALL(mock, callGetTotalHand(_, _))
    .Times(1)
    .WillOnce(Return(23));

    playGame.setHighestValidHandValueForPlayer(&mock, dealer, true);

    EXPECT_EQ(dealer->getCurrentTotal(), 23);
}




TEST(WinnerHandler_GetListOfPlayersWithHighestScoresShould, ReturnVectorOfSizeOneWhenOnlyOnePlayerHasTheHighestScore) {
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

TEST(WinnerHandler_GetListOfPlayersWithHighestScoresShould, ReturnOnePlayersValueWhenOnlyOnePlayerHasTheHighestScore) {
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

TEST(WinnerHandler_GetListOfPlayersWithHighestScoresShould, ReturnTwoPlayersWhenBothHaveHighest) {
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

TEST(WinnerHandler_GetListOfPlayersWithHighestScoresShould, ReturnOnePlayersValueWhenOnlyOnePlayerHasTheHighestScoreUnder21) {
    MockGame mock;
    PlayGame playGame;
    Player* player = new Player();
    Player* player2 = new Player();

    vector<Player*> players = {player, player2};
    playGame.setPlayerList(players);

    EXPECT_CALL(mock, callGetCurrentTotal(_))
    .Times(2)
    .WillOnce(Return(21))
    .WillOnce(Return(22));

    pair<int, vector<int>> actual = playGame.getListOfPlayersWithHighestScores(&mock);

    EXPECT_EQ(actual.second.back(), 0);
}