#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "game/playgame.h"
#include <vector>
#include <sstream
using namespace std;

TEST(VerifyHandHasWonShould, ReturnTrueWhenHandIs21WithoutAce) {
    PlayGame playGame;
    Player* player = new Player();
    Card cardHearts("hearts", "five");
    player->addCardToHand(cardHearts);
    Card cardSpades("spades", "five");
    player->addCardToHand(cardSpades);
    Card cardDiamonds("diamonds", "five");
    player->addCardToHand(cardDiamonds);
    Card cardClubs("clubs", "six");
    player->addCardToHand(cardClubs);

    bool actual = playGame.verifyHandHasWon(player->getHand());
    EXPECT_EQ(actual, true);    
}

TEST(VerifyHandHasWonShould, ReturnFalseWhenHandIsnt21WithoutAce) {
    PlayGame playGame;
    Player* player = new Player();
    Card cardHearts("hearts", "five");
    player->addCardToHand(cardHearts);

    bool actual = playGame.verifyHandHasWon(player->getHand());
    EXPECT_EQ(actual, false);    
}

TEST(VerifyHandHasWonShould, ReturnTrueWhenHandIs21WithOneAceAsElevenButStillEqualTo21) {
    PlayGame playGame;
    Player* player = new Player();
    Card cardHearts("hearts", "two");
    player->addCardToHand(cardHearts);
    Card cardSpades("spades", "ace");
    player->addCardToHand(cardSpades);
    Card cardDiamonds("diamonds", "ace");
    player->addCardToHand(cardDiamonds);
    Card cardClubs("clubs", "seven");
    player->addCardToHand(cardClubs);

    bool actual = playGame.verifyHandHasWon(player->getHand());
    EXPECT_EQ(actual, true);    
}

TEST(VerifyHandHasWonShould, ReturnTrueWhenHandIs21WithAceAsOne) {
    PlayGame playGame;
    Player* player = new Player();
    Card cardHearts("hearts", "ten");
    player->addCardToHand(cardHearts);
    Card cardSpades("spades", "ten");
    player->addCardToHand(cardSpades);
    Card cardClubs("clubs", "ace");
    player->addCardToHand(cardClubs);

    bool actual = playGame.verifyHandHasWon(player->getHand());
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


TEST(CheckIfHandHasWonShould, ReturnFalseWhenHandIsnt21) {
    PlayGame playGame;
    Player* player = new Player();
    Card cardHearts("hearts", "ten");
    player->addCardToHand(cardHearts);
    Card cardClubs("clubs", "ace");
    player->addCardToHand(cardClubs);

    bool actual = playGame.checkIfHandHasWon(player->getHand(), 1);
    EXPECT_EQ(actual, false);    
}

TEST(CheckIfHandHasWonShould, ReturnTrueWhenHandIs21WithAceAsOne) {
    PlayGame playGame;
    Player* player = new Player();
    Card cardHearts("hearts", "ten");
    player->addCardToHand(cardHearts);
    Card cardSpades("spades", "ten");
    player->addCardToHand(cardSpades);
    Card cardClubs("clubs", "ace");
    player->addCardToHand(cardClubs);

    bool actual = playGame.checkIfHandHasWon(player->getHand(), 1);
    EXPECT_EQ(actual, true);    
}

TEST(CheckIfHandHasWonShould, ReturnTrueWhenHandIs21WithOneAceAsElevenButStillEqualTo21) {
    PlayGame playGame;
    Player* player = new Player();
    Card cardHearts("hearts", "two");
    player->addCardToHand(cardHearts);
    Card cardSpades("spades", "ace");
    player->addCardToHand(cardSpades);
    Card cardDiamonds("diamonds", "ace");
    player->addCardToHand(cardDiamonds);
    Card cardClubs("clubs", "seven");
    player->addCardToHand(cardClubs);

    bool actual = playGame.checkIfHandHasWon(player->getHand(), 11);
    EXPECT_EQ(actual, true);    
}

TEST(CheckIfHandHasWonShould, ReturnTrueWhenHandIs21WithoutAce) {
    PlayGame playGame;
    Player* player = new Player();
    Card cardHearts("hearts", "five");
    player->addCardToHand(cardHearts);
    Card cardSpades("spades", "five");
    player->addCardToHand(cardSpades);
    Card cardDiamonds("diamonds", "five");
    player->addCardToHand(cardDiamonds);
    Card cardClubs("clubs", "six");
    player->addCardToHand(cardClubs);

    bool actual = playGame.checkIfHandHasWon(player->getHand());
    EXPECT_EQ(actual, true);    
}

TEST(CheckIfHandHasWonShould, ReturnFalseWhenHandIsnt21WithoutAce) {
    PlayGame playGame;
    Player* player = new Player();
    Card cardHearts("hearts", "five");
    player->addCardToHand(cardHearts);

    bool actual = playGame.checkIfHandHasWon(player->getHand());
    EXPECT_EQ(actual, false);    
}


TEST(VerifyAnyPlayerHasAchieved21Should, ReturnOneIfOnePlayerHasWon){
    PlayGame playGame;
    Player* player = new Player();
    Card cardHearts("hearts", "ten");
    player->addCardToHand(cardHearts);
    Card cardSpades("spades", "ten");
    player->addCardToHand(cardSpades);
    Card cardClubs("clubs", "ace");
    player->addCardToHand(cardClubs);
    vector<Player*> players = {player};
    playGame.setPlayerList(players);
    
    vector<int> actual = playGame.verifyAnyPlayerHasAchieved21();
    EXPECT_EQ(actual.size(), 1);    
}

TEST(VerifyAnyPlayerHasAchieved21Should, ReturnZeroIfNoPlayersHaveWon){
    PlayGame playGame;
    Player* player = new Player();
    Card cardHearts("hearts", "ten");
    player->addCardToHand(cardHearts);
    Card cardSpades("spades", "two");
    player->addCardToHand(cardSpades);
    Card cardClubs("clubs", "two");
    player->addCardToHand(cardClubs);
    vector<Player*> players = {player};
    playGame.setPlayerList(players);
    
    vector<int> actual = playGame.verifyAnyPlayerHasAchieved21();
    EXPECT_EQ(actual.size(),0);    
}


TEST(VerifyAnyPlayerHasAchieved21Should, ReturnTwoIfSecondOfTwoPlayersHaveWon){
    PlayGame playGame;
    Player* player = new Player();
    Card cardHearts("hearts", "ten");
    player->addCardToHand(cardHearts);
    Card cardSpades("spades", "two");
    player->addCardToHand(cardSpades);
    Card cardClubs("clubs", "ace");
    player->addCardToHand(cardClubs);


    Player* player2 = new Player();
    Card cardHearts2("hearts", "ten");
    player2->addCardToHand(cardHearts2);
    Card cardSpades2("spades", "ten");
    player2->addCardToHand(cardSpades2);
    Card cardClubs2("clubs", "ace");
    player2->addCardToHand(cardClubs2);



    vector<Player*> players = {player, player2};
    playGame.setPlayerList(players);
    
    vector<int> actual = playGame.verifyAnyPlayerHasAchieved21();
    EXPECT_EQ(actual.back(), 1);    
}


TEST(CheckIfHandHasGoneBustShould, ReturnFalseWhenUnder21) {
    PlayGame playGame;
    Player* player = new Player();
    Card card("hearts", "one");
    player->addCardToHand(card);

    bool actual = playGame.checkIfHandHasGoneBust(player->getHand());

    EXPECT_EQ(actual, false);
}

TEST(CheckIfHandHasGoneBustShould, ReturnTrueWhenOver21) {
    PlayGame playGame;
    Player* player = new Player();
    Card cardHearts("hearts", "ten");
    player->addCardToHand(cardHearts);
    Card cardSpades("spades", "ten");
    player->addCardToHand(cardSpades);
    Card cardClubs("clubs", "ten");
    player->addCardToHand(cardClubs);

    bool actual = playGame.checkIfHandHasGoneBust(player->getHand());

    EXPECT_EQ(actual, true);
}

TEST(CheckIfHandHasGoneBustShould, ReturnFalseWhenExactly21) {
    PlayGame playGame;
    Player* player = new Player();
    Card cardHearts("hearts", "ten");
    player->addCardToHand(cardHearts);
    Card cardSpades("spades", "ten");
    player->addCardToHand(cardSpades);
    Card cardClubs("clubs", "ace");
    player->addCardToHand(cardClubs);

    bool actual = playGame.checkIfHandHasGoneBust(player->getHand());

    EXPECT_EQ(actual, false);
}