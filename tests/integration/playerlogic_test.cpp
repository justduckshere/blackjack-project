#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "game/playgame.h"
#include <vector>
#include <sstream>
#include "../wrapper.h"

using namespace std;
using ::testing::Return;
using ::testing::_;

TEST(PlayPlayersRoundShould, IncreaseThePlayersHandWhenTheyRequest) {
    MockGame mock;
    PlayGame wrapper;
    PlayGame playGame;
    Deck deck;
    deck.init();
    Player* player = new Player();
    Card cardHearts("hearts", "two");
    player->addCardToHand(cardHearts);
    Card cardSpades("spades", "two");
    player->addCardToHand(cardSpades);
    vector<Player*> players = {player};

    playGame.setPlayerList(players);

    EXPECT_CALL(mock, getUserIntResponse())
    .Times(1)
    .WillOnce(Return(1));

    EXPECT_CALL(mock, callGetPlayerHasGoneBust(_))
    .Times(1)
    .WillOnce(Return(player->getPlayerHasGoneBust()));
    
    EXPECT_CALL(mock, callDealToPlayer(_, _))
    .Times(1)
    .WillOnce([&playGame](PlayGameWrapper* wrapper, int playerNumber){
        playGame.dealToPlayer(wrapper, playerNumber);
    });

    EXPECT_CALL(mock, callAddCardToHand(_, _))
    .Times(1)
    .WillOnce([&cardHearts](Player* player, Card card){
        player->addCardToHand(cardHearts);
    });

    EXPECT_CALL(mock, callGetDeck(_))
    .Times(1)
    .WillOnce(Return(deck.getDeck()));

    EXPECT_CALL(mock, callGetHand(_))
    .Times(3)
    .WillRepeatedly(Return(player->getHand()));

    playGame.playPlayersRound(&mock);

    EXPECT_EQ(playGame.getPlayerList()[0]->getHand().size(), 3);
}

TEST(PlayPlayersRoundShould, NotIncreaseThePlayersHandWhenTheyDoNotRequest) {
    MockGame mock;
    PlayGame playGame;
    Player* player = new Player();
    Card cardHearts("hearts", "two");
    player->addCardToHand(cardHearts);
    Card cardSpades("spades", "two");
    player->addCardToHand(cardSpades);
    vector<Player*> players = {player};

    playGame.setPlayerList(players);

    EXPECT_CALL(mock, callGetPlayerHasGoneBust(_))
    .Times(1)
    .WillOnce(Return(player->getPlayerHasGoneBust()));

    EXPECT_CALL(mock, getUserIntResponse())
    .WillOnce(Return(0));

    playGame.playPlayersRound(&mock);

    EXPECT_EQ(playGame.getPlayerList()[0]->getHand().size(), 2);
}

TEST(PlayPlayersRoundShould, NotIncreaseThePlayersHandWhenThePlayerHasGoneBust) {
    MockGame mock;
    PlayGame playGame;
    Player* player = new Player();
    vector<Player*> players = {player};
    player->setPlayerHasGoneBust();
    playGame.setPlayerList(players);

    EXPECT_CALL(mock, callGetPlayerHasGoneBust(_))
    .Times(1)
    .WillOnce(Return(player->getPlayerHasGoneBust()));

    playGame.playPlayersRound(&mock);

    EXPECT_EQ(playGame.getPlayerList()[0]->getHand().size(), 0);
}

TEST(PlayPlayersRoundShould, SetTheHandHasGoneBustWhenItHas) {
    MockGame mock;
    PlayGame wrapper;
    PlayGame playGame;
    Deck deck;
    deck.init();
    Player* player = new Player();
    Card cardHearts("hearts", "ten");
    player->addCardToHand(cardHearts);
    Card cardSpades("spades", "ten");
    player->addCardToHand(cardSpades);
    vector<Player*> players = {player};

    vector<Card> finalHand = {cardHearts, cardSpades, cardHearts};

    playGame.setPlayerList(players);

    EXPECT_CALL(mock, getUserIntResponse())
    .Times(1)
    .WillOnce(Return(1));

    EXPECT_CALL(mock, callGetPlayerHasGoneBust(_))
    .Times(1)
    .WillOnce(Return(player->getPlayerHasGoneBust()));
    
    EXPECT_CALL(mock, callDealToPlayer(_, _))
    .Times(1)
    .WillOnce([&playGame](PlayGameWrapper* wrapper, int playerNumber){
        playGame.dealToPlayer(wrapper, playerNumber);
    });

    EXPECT_CALL(mock, callAddCardToHand(_, _))
    .Times(1)
    .WillOnce([&cardHearts](Player* player, Card card){
        player->addCardToHand(cardHearts);
    });

    EXPECT_CALL(mock, callGetDeck(_))
    .Times(1)
    .WillOnce(Return(deck.getDeck()));

    EXPECT_CALL(mock, callGetHand(_))
    .Times(3)
    .WillRepeatedly(Return(player->getHand()));

    EXPECT_CALL(mock, callDisplayHand(_))
    .Times(1)
    .WillOnce([](Player* player){
        player->displayHand();
    });

    EXPECT_CALL(mock, callHandHasGoneBust(_, _))
    .Times(1)
    .WillOnce(Return(true));

        
    playGame.playPlayersRound(&mock);

    EXPECT_EQ(player->getPlayerHasGoneBust(), true);
}