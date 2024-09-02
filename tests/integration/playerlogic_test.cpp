#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "game/playgame.h"
#include <vector>
#include <sstream>

using namespace std;
using ::testing::Return;


class MockPlayGameInput :  public PlayGameWrapper{
public:
    MOCK_METHOD(int, getUserIntResponse, (), (override));
};

TEST(GetPlayerListShould, ReturnAnEmptyVectorTypeAfterInitialisation) {
    PlayGame playGame;
    vector<Player*> playerList = playGame.getPlayerList();
    EXPECT_EQ(playerList.size(), 0);
}


TEST(PlayPlayersRoundShould, IncreaseThePlayersHandWhenTheyRequest) {
    MockPlayGameInput mockPlayGameInput;
    PlayGame playGame;
    Player* player = new Player();
    Card cardHearts("hearts", "two");
    player->addCardToHand(cardHearts);
    Card cardSpades("spades", "two");
    player->addCardToHand(cardSpades);
    vector<Player*> players = {player};

    playGame.setPlayerList(players);

    EXPECT_CALL(mockPlayGameInput, getUserIntResponse())
    .WillOnce(Return(1));

    playGame.playPlayersRound(&mockPlayGameInput);

    EXPECT_EQ(playGame.getPlayerList()[0]->getHand().size(), 3);
}

TEST(PlayPlayersRoundShould, NotIncreaseThePlayersHandWhenTheyDoNotRequest) {
    MockPlayGameInput mockPlayGameInput;
    PlayGame playGame;
    Player* player = new Player();
    Card cardHearts("hearts", "two");
    player->addCardToHand(cardHearts);
    Card cardSpades("spades", "two");
    player->addCardToHand(cardSpades);
    vector<Player*> players = {player};

    playGame.setPlayerList(players);

    EXPECT_CALL(mockPlayGameInput, getUserIntResponse())
    .WillOnce(Return(0));

    playGame.playPlayersRound(&mockPlayGameInput);

    EXPECT_EQ(playGame.getPlayerList()[0]->getHand().size(), 2);
}

TEST(PlayPlayersRoundShould, NotIncreaseThePlayersHandWhenThePlayerHasGoneBust) {
    MockPlayGameInput mockPlayGameInput;
    PlayGame playGame;
    Player* player = new Player();
    vector<Player*> players = {player};
    player->setPlayerHasGoneBust();
    playGame.setPlayerList(players);

    playGame.playPlayersRound(&mockPlayGameInput);

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
    MockPlayGameInput mockPlayGameInput;

    EXPECT_CALL(mockPlayGameInput, getUserIntResponse())
    .WillOnce(Return(2));

    PlayGame playGame;
    playGame.createPlayerList(&mockPlayGameInput);

    EXPECT_EQ(playGame.getPlayerList().size(), 2);
}

TEST(CreatePlayerListShould, CreateOnePlayerWhenOneIsCreated) {
    MockPlayGameInput mockPlayGameInput;
    
    EXPECT_CALL(mockPlayGameInput, getUserIntResponse())
    .WillOnce(Return(1));

    PlayGame playGame;
    playGame.createPlayerList(&mockPlayGameInput);

    EXPECT_EQ(playGame.getPlayerList().size(), 1);
}