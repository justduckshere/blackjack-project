#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "game/playgame.h"
#include <vector>
#include <sstream>
using namespace std;


TEST(GameLogic_Handis21Should, ReturnFalseWhenHandIsnt21WithoutAce) {
    PlayGame playGame;
    Player* player = new Player();
    PlayGameWrapper* wrapper = new PlayGame();
    Card cardHearts("hearts", "five");
    player->addCardToHand(cardHearts);

    bool actual = playGame.handis21(wrapper, player->getHand());
    EXPECT_EQ(actual, false);    
}

TEST(GameLogic_Handis21Should, ReturnFalseWhenHandIsnt21WithAce) {
    PlayGame playGame;
    Player* player = new Player();
    PlayGameWrapper* wrapper = new PlayGame();
    Card cardHearts("hearts", "ace");
    player->addCardToHand(cardHearts);

    bool actual = playGame.handis21(wrapper, player->getHand());
    EXPECT_EQ(actual, false);    
}

TEST(GameLogic_Handis21Should, ReturnTrueWhenHandIs21WithoutAce) {
    PlayGame playGame;
    Player* player = new Player();
    PlayGameWrapper* wrapper = new PlayGame();
    Card cardHearts("hearts", "five");
    player->addCardToHand(cardHearts);
    Card cardSpades("spades", "five");
    player->addCardToHand(cardSpades);
    Card cardDiamonds("diamonds", "five");
    player->addCardToHand(cardDiamonds);
    Card cardClubs("clubs", "six");
    player->addCardToHand(cardClubs);

    bool actual = playGame.handis21(wrapper, player->getHand());
    EXPECT_EQ(actual, true);    
}

TEST(GameLogic_Handis21Should, ReturnTrueWhenHandIs21WithMultipleAces) {
    PlayGame playGame;
    Player* player = new Player();
    PlayGameWrapper* wrapper = new PlayGame();
    Card cardHearts("hearts", "two");
    player->addCardToHand(cardHearts);
    Card cardSpades("spades", "ace");
    player->addCardToHand(cardSpades);
    Card cardDiamonds("diamonds", "ace");
    player->addCardToHand(cardDiamonds);
    Card cardClubs("clubs", "seven");
    player->addCardToHand(cardClubs);

    bool actual = playGame.handis21(wrapper, player->getHand(), 11);
    EXPECT_EQ(actual, true);    
}

TEST(GameLogic_Handis21Should, ReturnTrueWhenHandIs21WithOneAce) {
    PlayGame playGame;
    Player* player = new Player();
    PlayGameWrapper* wrapper = new PlayGame();
    Card cardHearts("hearts", "ten");
    player->addCardToHand(cardHearts);
    Card cardClubs("clubs", "ace");
    player->addCardToHand(cardClubs);

    bool actual = playGame.handis21(wrapper, player->getHand(), 11);
    EXPECT_EQ(actual, true);    
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

TEST(GameLogic_ReturnListOfPlayersAt21, ReturnOneIfOnePlayerHasWon){
    PlayGame playGame;
    Player* player = new Player();
    PlayGameWrapper* wrapper = new PlayGame();
    Card cardHearts("hearts", "ten");
    player->addCardToHand(cardHearts);
    Card cardSpades("spades", "ten");
    player->addCardToHand(cardSpades);
    Card cardClubs("clubs", "ace");
    player->addCardToHand(cardClubs);
    vector<Player*> players = {player};
    playGame.setPlayerList(players);
    
    vector<int> actual = playGame.returnListOfPlayersAt21(wrapper);
    EXPECT_EQ(actual.size(), 1);    
}

TEST(GameLogic_ReturnListOfPlayersAt21, ReturnZeroIfNoPlayersHaveWon){
    PlayGame playGame;
    Player* player = new Player();
    PlayGameWrapper* wrapper = new PlayGame();
    Card cardHearts("hearts", "ten");
    player->addCardToHand(cardHearts);
    Card cardSpades("spades", "two");
    player->addCardToHand(cardSpades);
    Card cardClubs("clubs", "two");
    player->addCardToHand(cardClubs);
    vector<Player*> players = {player};
    playGame.setPlayerList(players);
    
    vector<int> actual = playGame.returnListOfPlayersAt21(wrapper);
    EXPECT_EQ(actual.size(),0);    
}

TEST(GameLogic_ReturnListOfPlayersAt21, ReturnTwoIfSecondOfTwoPlayersHaveWon){
    PlayGame playGame;
    Player* player = new Player();
    PlayGameWrapper* wrapper = new PlayGame();
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
    
    vector<int> actual = playGame.returnListOfPlayersAt21(wrapper);
    EXPECT_EQ(actual.back(), 1);    
}


TEST(GameLogic_HandHasGoneBustShould, ReturnFalseWhenUnder21) {
    PlayGame playGame;
    Player* player = new Player();
    PlayGameWrapper* wrapper = new PlayGame();
    Card card("hearts", "one");
    player->addCardToHand(card);

    bool actual = playGame.handHasGoneBust(wrapper, player->getHand());

    EXPECT_EQ(actual, false);
}

TEST(GameLogic_HandHasGoneBustShould, ReturnTrueWhenOver21) {
    PlayGame playGame;
    Player* player = new Player();
    PlayGameWrapper* wrapper = new PlayGame();
    Card cardHearts("hearts", "ten");
    player->addCardToHand(cardHearts);
    Card cardSpades("spades", "ten");
    player->addCardToHand(cardSpades);
    Card cardClubs("clubs", "ten");
    player->addCardToHand(cardClubs);

    bool actual = playGame.handHasGoneBust(wrapper, player->getHand());

    EXPECT_EQ(actual, true);
}

TEST(GameLogic_HandHasGoneBustShould, ReturnFalseWhenExactly21) {
    PlayGame playGame;
    Player* player = new Player();
    PlayGameWrapper* wrapper = new PlayGame();
    Card cardHearts("hearts", "ten");
    player->addCardToHand(cardHearts);
    Card cardSpades("spades", "ten");
    player->addCardToHand(cardSpades);
    Card cardClubs("clubs", "ace");
    player->addCardToHand(cardClubs);

    bool actual = playGame.handHasGoneBust(wrapper, player->getHand());

    EXPECT_EQ(actual, false);
}


TEST(GameLogic_AllPlayersHaveGoneBustShould, ReturnTrueWhenAllPlayersHaveGoneBust) {
    PlayGame playGame;
    Player* player = new Player();
    Player* player2 = new Player();
    PlayGameWrapper* wrapper = new PlayGame();
    Card cardHearts("hearts", "ten");
    player->addCardToHand(cardHearts);
    player2->addCardToHand(cardHearts);
    Card cardSpades("spades", "ten");
    player->addCardToHand(cardSpades);
    player2->addCardToHand(cardSpades);
    Card cardClubs("clubs", "ten");
    player->addCardToHand(cardClubs);
    player2->addCardToHand(cardClubs);
    vector<Player*> players = {player, player2};
    playGame.setPlayerList(players);

    bool actual = playGame.allPlayersHaveGoneBust(wrapper);

    EXPECT_EQ(actual, true);
}

TEST(GameLogic_AllPlayersHaveGoneBustShould, ReturnFalseWhenOnePlayerHasntGoneBust) {
    PlayGame playGame;
    Player* player = new Player();
    Player* player2 = new Player();
    PlayGameWrapper* wrapper = new PlayGame();
    Card cardHearts("hearts", "ten");
    player->addCardToHand(cardHearts);
    player2->addCardToHand(cardHearts);
    Card cardSpades("spades", "ten");
    player->addCardToHand(cardSpades);
    player2->addCardToHand(cardSpades);
    Card cardClubs("clubs", "ten");
    player->addCardToHand(cardClubs);
    vector<Player*> players = {player, player2};
    playGame.setPlayerList(players);

    bool actual = playGame.allPlayersHaveGoneBust(wrapper);

    EXPECT_EQ(actual, false);
}

TEST(GameLogic_AllPlayersHaveGoneBustShould, ReturnFalseWhenNoPlayersHaveGoneBust) {
    PlayGame playGame;
    Player* player = new Player();
    Player* player2 = new Player();
    PlayGameWrapper* wrapper = new PlayGame();
    Card cardHearts("hearts", "ten");
    player->addCardToHand(cardHearts);
    player2->addCardToHand(cardHearts);
    Card cardSpades("spades", "ten");
    player->addCardToHand(cardSpades);
    player2->addCardToHand(cardSpades);
    vector<Player*> players = {player, player2};
    playGame.setPlayerList(players);

    bool actual = playGame.allPlayersHaveGoneBust(wrapper);

    EXPECT_EQ(actual, false);
}

