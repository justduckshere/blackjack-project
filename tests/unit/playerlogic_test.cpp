#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "game/playgame.h"
#include "wrapper.h"
#include <vector>
#include <sstream>

using namespace std;
using ::testing::Return;
using ::testing::_;

TEST(GetPlayerListShould, ReturnAnEmptyVectorTypeAfterInitialisation) {
    PlayGame playGame;
    vector<Player*> playerList = playGame.getPlayerList();
    EXPECT_EQ(playerList.size(), 0);
}

TEST(PlayPlayersRoundShould, PrintSetTextWhenBeingDealtCard) {
    MockGame mock;

    stringstream buffer;
    streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf());
    
    PlayGame playGame;
    Player* player = new Player();
    Card cardHearts("hearts", "two");
    player->addCardToHand(cardHearts);
    Card cardSpades("spades", "two");
    player->addCardToHand(cardSpades);
    vector<Card> hand = {cardHearts, cardSpades};
    vector<Player*> players = {player};

    playGame.setPlayerList(players);

    EXPECT_CALL(mock, callGetPlayerHasGoneBust(_))
    .Times(1)
    .WillOnce(Return(false));

    EXPECT_CALL(mock, getUserIntResponse())
    .WillOnce(Return(1));

    EXPECT_CALL(mock, callDealToPlayer(_, _))
    .Times(1)
    .WillOnce([&hand](PlayGameWrapper* wrapper, int playerNumber) {
        cout << "EXAMPLE TEXT IS HERE";
    }); 
    EXPECT_CALL(mock, callCheckIfHandHasGoneBust(_, _))
    .Times(1)
    .WillOnce(Return(false));

    playGame.playPlayersRound(&mock);

    string text = buffer.str();
    cout.rdbuf(prevcoutbuf);

    EXPECT_EQ(text, "Would Player 1 like another card (1 = yes, 0 = no)\nEXAMPLE TEXT IS HERE\tPlayer 1 has ");
}

TEST(PlayPlayersRoundShould, PrintPlayerHasGoneBustWhenTheyHave) {
    MockGame mock;

    stringstream buffer;
    streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf());
    
    PlayGame playGame;
    Player* player = new Player();
    Card cardHearts("hearts", "two");
    player->addCardToHand(cardHearts);
    Card cardSpades("spades", "two");
    player->addCardToHand(cardSpades);
    vector<Card> hand = {cardHearts, cardSpades};
    vector<Player*> players = {player};

    playGame.setPlayerList(players);

    EXPECT_CALL(mock, callGetPlayerHasGoneBust(_))
    .Times(1)
    .WillOnce(Return(false));

    EXPECT_CALL(mock, getUserIntResponse())
    .WillOnce(Return(1));

    EXPECT_CALL(mock, callCheckIfHandHasGoneBust(_, _))
    .Times(1)
    .WillOnce(Return(true));

    playGame.playPlayersRound(&mock);

    string text = buffer.str();
    cout.rdbuf(prevcoutbuf);

    EXPECT_EQ(text, "Would Player 1 like another card (1 = yes, 0 = no)\n\tPlayer 1 has Sorry - you have gone bust!\n\n");
}

TEST(PlayPlayersRoundShould, IncreaseThePlayersHandWhenTheyRequest) {
    MockGame mock;
    PlayGame playGame;
    Player* player = new Player();
    Card cardHearts("hearts", "two");
    player->addCardToHand(cardHearts);
    Card cardSpades("spades", "two");
    player->addCardToHand(cardSpades);
    vector<Card> hand = {cardHearts, cardSpades};
    vector<Player*> players = {player};

    playGame.setPlayerList(players);

    EXPECT_CALL(mock, callGetPlayerHasGoneBust(_))
    .Times(1)
    .WillOnce(Return(false));

    EXPECT_CALL(mock, callDealToPlayer(_, _))
    .Times(1)
    .WillOnce([&hand](PlayGameWrapper* wrapper, int playerNumber) {
        Card cardDiamond("diamond", "three");
        hand.push_back(cardDiamond);
    });

    EXPECT_CALL(mock, callDisplayHand(_))
    .Times(1);

    EXPECT_CALL(mock, getUserIntResponse())
    .WillOnce(Return(1));

    playGame.playPlayersRound(&mock);

    EXPECT_EQ(hand.size(), 3);
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
    .WillOnce(Return(false));

    EXPECT_CALL(mock, getUserIntResponse())
    .Times(1)
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
    .WillOnce(Return(true));

    EXPECT_CALL(mock, getUserIntResponse())
    .Times(0);

    playGame.playPlayersRound(&mock);

    EXPECT_EQ(playGame.getPlayerList()[0]->getHand().size(), 0);
}


TEST(SetPlayerListShould, PopulatePlayerListWithOnePlayerGivenOnePlayer) {
    PlayGame playGame;
    Player* player = new Player();
    vector<Player*> players = {player};

    playGame.setPlayerList(players);

    EXPECT_EQ(playGame.getPlayerList().size(), 1);
}

TEST(SetPlayerListShould, PopulatePlayerListWithTwoPlayersGivenTwoPlayers) {
    PlayGame playGame;
    Player* player = new Player();
    vector<Player*> players = {player, player};

    playGame.setPlayerList(players);

    EXPECT_EQ(playGame.getPlayerList().size(), 2);
}


TEST(CreatePlayerListShould, CreateTwoPlayersWhenTwoAreCreated) {
    MockGame mock;
    EXPECT_CALL(mock, getUserIntResponse())
    .WillOnce(Return(2));

    PlayGame playGame;
    playGame.createPlayerList(&mock);

    EXPECT_EQ(playGame.getPlayerList().size(), 2);
}

TEST(CreatePlayerListShould, CreateOnePlayerWhenOneIsCreated) {
    MockGame mock;
    
    EXPECT_CALL(mock, getUserIntResponse())
    .WillOnce(Return(1));

    PlayGame playGame;
    playGame.createPlayerList(&mock);

    EXPECT_EQ(playGame.getPlayerList().size(), 1);
}

TEST(CreatePlayerListShould, PrintOnePlayerWhenOneIsToldToBeMade) {
    MockGame mock;

    stringstream buffer;
    streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf());

    EXPECT_CALL(mock, getUserIntResponse())
    .WillOnce(Return(2));

    PlayGame playGame;
    playGame.createPlayerList(&mock);

    string text = buffer.str();
    cout.rdbuf(prevcoutbuf);


    EXPECT_EQ(text, "How many players are playing blackjack? (please pick a number between 1 and 7)\n\t\tWe have 2 people playing Blackjack (plus a dealer)\n\n");
}