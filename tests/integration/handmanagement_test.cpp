#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "game/playgame.h"
#include <vector>
#include <sstream>

using namespace std;
using ::testing::Return;



TEST(DealToEveryoneShould, IncreaseBothPlayersHandSizesByOne) {
    PlayGameWrapper* playGameWrapper = new PlayGame();
    PlayGame playGame;
    Player* player = new Player();
    Player* player2 = new Player();
    vector<Player*> players = {player, player2};
    Player* dealer = new Player();

    Deck* deck = new Deck();
    playGame.setCurrentDeck(*deck);

    playGame.setDealer(dealer);
    playGame.setPlayerList(players);
    playGame.dealToEveryone(playGameWrapper);

    EXPECT_EQ(playGame.getPlayerList()[0]->getHand().size(), 1);
    EXPECT_EQ(playGame.getPlayerList()[1]->getHand().size(), 1);
    
}

TEST(DealToEveryoneShould, IncreasePlayersHandSizesByTwoWhenCalledTwice) {
    PlayGameWrapper* playGameWrapper = new PlayGame();
    PlayGame playGame;
    Player* player = new Player();
    Player* dealer = new Player();
    vector<Player*> players = {player};

    playGame.setDealer(dealer);
    playGame.setPlayerList(players);
    playGame.dealToEveryone(playGameWrapper);
    playGame.dealToEveryone(playGameWrapper);

    EXPECT_EQ(playGame.getPlayerList()[0]->getHand().size(), 2);
}


TEST(DealToEveryoneShould, DecreaseTheDeckSizeByTwoForOnePlayer) {
    PlayGameWrapper* playGameWrapper = new PlayGame();
    PlayGame playGame;
    Player* player = new Player();
    vector<Player*> players = {player};
    Player* dealer = new Player();

    playGame.setDealer(dealer);
    playGame.setPlayerList(players);
    playGame.dealToEveryone(playGameWrapper);

    EXPECT_EQ(playGame.getDeck().getDeck().size(), 50);
}

TEST(DealToPlayerShould, IncreaseThePlayersHandSize) {
    PlayGameWrapper* playGameWrapper = new PlayGame();
    PlayGame playGame;
    Player* player = new Player();
    vector<Player*> players = {player};

    playGame.setPlayerList(players);
    playGame.dealToPlayer(playGameWrapper, 0);
    EXPECT_EQ(playGame.getPlayerList()[0]->getHand().size(), 1);
    
}



TEST(GetTotalHandShould, ReturnZeroForNoneInHand) {
    PlayGameWrapper* playGameWrapper = new PlayGame();
    PlayGame playGame;
    vector<Card> hand = {};

    EXPECT_EQ(playGame.getTotalHand(playGameWrapper, hand), 0);
}

TEST(GetTotalHandShould, ReturnTwentyForTotalOfTwentyInHand) {
    PlayGameWrapper* playGameWrapper = new PlayGame();
    PlayGame playGame;
    vector<Card> hand = {};
    Card cardHearts("hearts", "ten");
    hand.push_back(cardHearts);
    Card cardSpades("spades", "jack");
    hand.push_back(cardSpades);

    EXPECT_EQ(playGame.getTotalHand(playGameWrapper, hand), 20);
}

TEST(GetTotalHandShould, Return20GivenNineAndAce) {
    PlayGameWrapper* playGameWrapper = new PlayGame();
    PlayGame playGame;
    vector<Card> hand = {};
    Card cardHearts("hearts", "nine");
    hand.push_back(cardHearts);
    Card cardSpades("spades", "ace");
    hand.push_back(cardSpades);

    EXPECT_EQ(playGame.getTotalHand(playGameWrapper, hand, 11), 20);
}

TEST(GetTotalHandShould, Return13GivenThreeAces) {
    PlayGameWrapper* playGameWrapper = new PlayGame();
    PlayGame playGame;
    vector<Card> hand = {};
    Card cardHearts("hearts", "ace");
    hand.push_back(cardHearts);
    Card cardSpades("spades", "ace");
    hand.push_back(cardSpades);
    Card cardClubs("clubs", "ace");
    hand.push_back(cardClubs);

    EXPECT_EQ(playGame.getTotalHand(playGameWrapper, hand, 11), 13);
}

TEST(GetTotalHandShould, ReturnTenGivenNineAndAce) {
    PlayGameWrapper* playGameWrapper = new PlayGame();
    PlayGame playGame;
    vector<Card> hand = {};
    Card cardHearts("hearts", "nine");
    hand.push_back(cardHearts);
    Card cardSpades("spades", "ace");
    hand.push_back(cardSpades);


    EXPECT_EQ(playGame.getTotalHand(playGameWrapper, hand, 1), 10);
}