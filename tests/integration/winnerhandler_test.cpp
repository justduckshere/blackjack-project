#include <gtest/gtest.h>
#include "game/playgame.h"
#include <vector>
#include <sstream>


TEST(DetermineWinnerFromNobody21Should, PrintDealerAsWinnerGivenNoPlayers) {
    stringstream buffer;
    streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf());
    PlayGame playGame;
    Player* dealer = new Player();
    Card cardHearts("hearts", "ace");
    dealer->addCardToHand(cardHearts);
    Card cardSpades("spades", "ace");
    dealer->addCardToHand(cardSpades);
    playGame.setDealer(dealer);

    playGame.determineWinnerFromNobody21();

    string text = buffer.str();
    cout.rdbuf(prevcoutbuf);


    EXPECT_EQ("Dealer has won with a score of 12\n", text);
}

TEST(DetermineWinnerFromNobody21Should, PrintDealerAsWinnerGivenOnePlayerWithLesserScore) {
    stringstream buffer;
    streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf());
    PlayGame playGame;
    Player* dealer = new Player();
    Card cardHearts("hearts", "ace");
    dealer->addCardToHand(cardHearts);
    Card cardSpades("spades", "ace");
    dealer->addCardToHand(cardSpades);
    playGame.setDealer(dealer);

    Player* player = new Player();
    Card cardHearts2("hearts", "two");
    player->addCardToHand(cardHearts2);
    Card cardSpades2("spades", "two");
    player->addCardToHand(cardSpades2);
    vector<Player*> players = {player};
    playGame.setPlayerList(players);

    playGame.determineWinnerFromNobody21();

    string text = buffer.str();
    cout.rdbuf(prevcoutbuf);


    EXPECT_EQ("Dealer has won with a score of 12\n", text);
}

TEST(DetermineWinnerFromNobody21Should, PrintPlayerOneAsWinnerGivenPlayerHasHigherScore) {
    stringstream buffer;
    streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf());
    PlayGame playGame;
    Player* dealer = new Player();
    dealer->setCurrentTotal(10);
    playGame.setDealer(dealer);

    Player* player = new Player();
    player->setCurrentTotal(12);
    vector<Player*> players = {player};
    playGame.setPlayerList(players);

    playGame.determineWinnerFromNobody21();

    string text = buffer.str();
    cout.rdbuf(prevcoutbuf);


    EXPECT_EQ("Player 1 has won and with a score of 12\n\n", text);
}

TEST(DetermineWinnerFromNobody21Should, PrintPlayerOneAndTwoAsWinnersGivenPlayersHaveHighestScores) {
    stringstream buffer;
    streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf());
    PlayGame playGame;
    Player* dealer = new Player();
    dealer->setCurrentTotal(10);
    playGame.setDealer(dealer);

    Player* player = new Player();
    player->setCurrentTotal(13);

 
    Player* player2 = new Player();
    player2->setCurrentTotal(13);

    vector<Player*> players = {player, player2};
    playGame.setPlayerList(players);

    playGame.determineWinnerFromNobody21();

    string text = buffer.str();
    cout.rdbuf(prevcoutbuf);


    EXPECT_EQ("We have a tie!\nPlayer 1 has won with a score of: 13\n\nPlayer 2 has won with a score of: 13\n\n", text);
}

// TEST(DetermineWinnerFromNobody21Should, PrintPlayerOneAndTwoandDealerAsWinnersGivenPlayersHaveHighestScores) {
//     stringstream buffer;
//     streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf());
//     PlayGame playGame;
//     Player* dealer = new Player();
//     dealer->setCurrentTotal(13);
//     playGame.setDealer(dealer);

//     Player* player = new Player();
//     player->setCurrentTotal(13);

//     Player* player2 = new Player();
//     player2->setCurrentTotal(13);

//     vector<Player*> players = {player, player2};
//     playGame.setPlayerList(players);

//     playGame.determineWinnerFromNobody21();

//     string text = buffer.str();
//     cout.rdbuf(prevcoutbuf);


//     EXPECT_EQ("We have a tie!\nPlayer 1 has won with a score of: 13\n\nPlayer 2 has won with a score of: 13\n\nAnd Dealer has also achieved 13\n\n", text);
// }


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


TEST(setHighestValidHandValueForPlayerShould, ReturnTwentyGivenTwoJacksAndNoAce) {
    PlayGame playGame;
    Player* player = new Player();
    Card cardHearts("hearts", "jack");
    player->addCardToHand(cardHearts);
    Card cardSpades("spades", "jack");
    player->addCardToHand(cardSpades);

    playGame.setHighestValidHandValueForPlayer(player);

    EXPECT_EQ(player->getCurrentTotal(), 20);
}

TEST(setHighestValidHandValueForPlayerShould, Return20ForOneAceandANine) {
    PlayGame playGame;
    Player* player = new Player();
    Card cardHearts("hearts", "ace");
    player->addCardToHand(cardHearts);
    Card cardSpades("spades", "nine");
    player->addCardToHand(cardSpades);

    playGame.setHighestValidHandValueForPlayer(player);

    EXPECT_EQ(player->getCurrentTotal(), 20);
}

TEST(setHighestValidHandValueForPlayerShould, Return12ForTwoAces) {
    PlayGame playGame;
    Player* player = new Player();
    Card cardHearts("hearts", "ace");
    player->addCardToHand(cardHearts);
    Card cardSpades("spades", "ace");
    player->addCardToHand(cardSpades);

    playGame.setHighestValidHandValueForPlayer(player);

    EXPECT_EQ(player->getCurrentTotal(), 12);
}



TEST(GetListOfPlayersWithHighestScoresShould, ReturnOnePlayerWhenOnlyOnePlayerHasTheHighestScore) {
    PlayGame playGame;
    Player* player = new Player();
    player->setCurrentTotal(12);

    Player* player2 = new Player();
    player2->setCurrentTotal(4);

    vector<Player*> players = {player, player2};
    playGame.setPlayerList(players);

    pair<int, vector<int>> actual = playGame.getListOfPlayersWithHighestScores();

    EXPECT_EQ(actual.second.size(), 1);
}

TEST(GetListOfPlayersWithHighestScoresShould, ReturnOnePlayersValueWhenOnlyOnePlayerHasTheHighestScore) {
    PlayGame playGame;
    Player* player = new Player();
    player->setCurrentTotal(12);

    Player* player2 = new Player();
    player2->setCurrentTotal(4);

    vector<Player*> players = {player, player2};
    playGame.setPlayerList(players);

    pair<int, vector<int>> actual = playGame.getListOfPlayersWithHighestScores();

    EXPECT_EQ(actual.first, 12);
}

TEST(GetListOfPlayersWithHighestScoresShould, ReturnTwoPlayersWhenBothHaveHighest) {
    PlayGame playGame;
    Player* player = new Player();
    player->setCurrentTotal(12);

    Player* player2 = new Player();
    player2->setCurrentTotal(12);

    vector<Player*> players = {player, player2};
    playGame.setPlayerList(players);

    pair<int, vector<int>> actual = playGame.getListOfPlayersWithHighestScores();

    EXPECT_EQ(actual.second.size(), 2);
}