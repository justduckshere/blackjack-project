#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "game/playgame.h"
#include <vector>
#include <sstream>

using namespace std;
using ::testing::Return;

TEST(PlayGame_RegularGamePlayShould, PrintDealerHasGoneWhenDealerIsOver21) {
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

    // Setup for playplayersround call
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

}