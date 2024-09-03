#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "game/playgame.h"
#include "hand/card.h"
#include "hand/deck.h"
#include "../wrapper.h"
#include <sstream>
#include <iostream>

using namespace std;
using ::testing::Return;
using ::testing::_;
using ::testing::Field;
using ::testing::Invoke;

TEST(HandManagement_DealToEveryoneShould, HaveCardsPlacedInCorrectOrderWhenCalledTwice) {
    MockGame mock;
    PlayGame playGame;
    Player* player = new Player();
    vector<Card> hand = {};
    Card validCardForBackOfDeck("valid", "valid"); 
    vector<Card> validDeck = {validCardForBackOfDeck};
    vector<Player*> players = {player};
    playGame.setPlayerList(players);

    EXPECT_CALL(mock, callDealToPlayer(_, _))
    .Times(2)
    .WillOnce([&hand](PlayGameWrapper* wrapper, int playerNumber){
        Card card("hearts", "ace");
        hand.push_back(card);
    })
    .WillOnce([&hand](PlayGameWrapper* wrapper, int playerNumber){
        Card card2("hearts", "ten");
        hand.push_back(card2);
    });
    EXPECT_CALL(mock, callGetDeck(_))
    .Times(2)
    .WillRepeatedly(Return(validDeck));

    playGame.dealToEveryone(&mock);
    playGame.dealToEveryone(&mock);

    EXPECT_EQ(hand[0].getValue(), "ace");
    EXPECT_EQ(hand[1].getValue(), "ten");
}

TEST(HandManagement_DealToEveryoneShould, IncreasePlayersHandByOne) {
    MockGame mock;
    PlayGame playGame;
    Player* player = new Player();
    Card validCardForBackOfDeck("valid", "valid"); 
    vector<Card> validDeck = {validCardForBackOfDeck};
    vector<Card> hand = {};
    vector<Card> dealerHand = {};
    vector<Player*> players = {player};
    playGame.setPlayerList(players);

    EXPECT_CALL(mock, callDealToPlayer(_, _))
    .Times(1)
    .WillOnce([&hand](PlayGameWrapper* wrapper, int playerNumber){
        Card card("hearts", "ace");
        hand.push_back(card);
    });

    EXPECT_CALL(mock, callAddCardToHand(_, _))
    .Times(1)
    .WillOnce([&dealerHand](Player* player, Card card){
        Card card2("hearts", "ace");
        dealerHand.push_back(card2);
    });

    EXPECT_CALL(mock, callGetDeck(_))
    .Times(1)
    .WillRepeatedly(Return(validDeck));

    playGame.dealToEveryone(&mock);

    EXPECT_EQ(dealerHand.size(), 1);
    EXPECT_EQ(hand.size(), 1);
}

TEST(HandManagement_DealToEveryoneShould, IncreaseDealersHandByOne) {
    MockGame mock;
    PlayGame playGame;
    Card validCardForBackOfDeck("valid", "valid"); 
    vector<Card> validDeck = {validCardForBackOfDeck};
    vector<Card> dealerHand = {};

    EXPECT_CALL(mock, callAddCardToHand(_, _))
    .Times(1)
    .WillOnce([&dealerHand](Player* player, Card card){
        Card card2("hearts", "ace");
        dealerHand.push_back(card2);
    });

    EXPECT_CALL(mock, callGetDeck(_))
    .Times(1)
    .WillOnce(Return(validDeck));

    playGame.dealToEveryone(&mock);

    EXPECT_EQ(dealerHand.size(), 1);
}

TEST(HandManagement_DealToEveryoneShould, IncreaseBothPlayersHandSizesByOne) {
    MockGame mock;
    PlayGame playGame;
    Card validCardForBackOfDeck("valid", "valid"); 
    vector<Card> validDeck = {validCardForBackOfDeck};
    Player* player = new Player();
    vector<Card> hand1 = {};
    Player* player2 = new Player();
    vector<Card> hand2 = {};
    vector<Player*> players = {player, player2};
    playGame.setPlayerList(players);

    EXPECT_CALL(mock, callDealToPlayer(_, _))
    .Times(2)
    .WillOnce([&hand1](PlayGameWrapper* wrapper, int playerNumber){
        Card card("hearts", "ace");
        hand1.push_back(card);
    })
    .WillOnce([&hand2](PlayGameWrapper* wrapper, int playerNumber){
        Card card("hearts", "ace");
        hand2.push_back(card);
    });

    EXPECT_CALL(mock, callGetDeck(_))
    .Times(1)
    .WillRepeatedly(Return(validDeck));

    playGame.dealToEveryone(&mock);

    EXPECT_EQ(hand1.size(), 1);
    EXPECT_EQ(hand2.size(), 1);
    
}

TEST(HandManagement_DealToEveryoneShould, IncreasePlayersHandSizesByTwoWhenCalledTwice) {
    MockGame mock;
    PlayGame playGame;
    Card validCardForBackOfDeck("valid", "valid"); 
    vector<Card> validDeck = {validCardForBackOfDeck};
    Player* player = new Player();
    vector<Card> hand = {};
    vector<Player*> players = {player};

    EXPECT_CALL(mock, callDealToPlayer(_, _))
    .Times(2)
    .WillRepeatedly([&hand](PlayGameWrapper* wrapper, int playerNumber){
        Card card("hearts", "ace");
        hand.push_back(card);
    });

    EXPECT_CALL(mock, callGetDeck(_))
    .Times(2)
    .WillRepeatedly(Return(validDeck));

    playGame.setPlayerList(players);

    playGame.dealToEveryone(&mock);
    playGame.dealToEveryone(&mock);

    EXPECT_EQ(hand.size(), 2);
}

TEST(HandManagement_DealToEveryoneShould, DecreaseTheDeckSizeByTwoForOnePlayer) {
    MockGame mock;
    PlayGame playGame;
    Card validCardForBackOfDeck("valid", "valid"); 
    vector<Card> validDeck = {validCardForBackOfDeck};
    Player* player = new Player();
    vector<Player*> players = {player};
    playGame.setPlayerList(players);

    vector<int> deckVector = {1, 1, 1};

    EXPECT_CALL(mock, callDealToPlayer(_, _))
    .Times(1)
    .WillOnce([&deckVector](PlayGameWrapper* wrapper, int playerNumber){
        deckVector.pop_back();
    });

    EXPECT_CALL(mock, callRemovePlayedCard( _))
    .Times(1)
    .WillOnce([&deckVector](Deck deck){
        deckVector.pop_back();
    });

    EXPECT_CALL(mock, callGetDeck(_))
    .Times(1)
    .WillOnce(Return(validDeck));

    playGame.dealToEveryone(&mock);

    EXPECT_EQ(deckVector.size(), 1);
}



TEST(HandManagement_DealToPlayerShould, IncreaseThePlayersHandSize) {
    MockGame mock;
    PlayGame playGame;
    Card validCardForBackOfDeck("valid", "valid"); 
    vector<Card> validDeck = {validCardForBackOfDeck};
    Player* player = new Player();
    vector<Player*> players = {player};
    playGame.setPlayerList(players);

    Card card("heart", "one");
    vector<Card> returnedCards = {card};

    EXPECT_CALL(mock, callAddCardToHand(_, _))
    .Times(1)
    .WillOnce([&returnedCards](Player* player, Card card){
        player->addCardToHand(card);
    });

    EXPECT_CALL(mock, callGetHand(_))
    .Times(2)
    .WillOnce(Return(returnedCards))
    .WillOnce(Return(returnedCards));

    EXPECT_CALL(mock, callRemovePlayedCard( _))
    .Times(1);

    EXPECT_CALL(mock, callGetDeck(_))
    .Times(1)
    .WillOnce(Return(validDeck));

    playGame.dealToPlayer(&mock, 0);

    EXPECT_EQ(player->getHand().size(), 1);
}

TEST(HandManagement_DealToPlayerShould, PrintThePlayersDealtCard) {
    stringstream buffer;
    streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf());

    MockGame mock;
    PlayGame playGame;
    Card validCardForBackOfDeck("valid", "valid"); 
    vector<Card> validDeck = {validCardForBackOfDeck};
    Player* player = new Player();
    vector<Player*> players = {player};
    playGame.setPlayerList(players);

    Card card("heart", "ace");
    vector<Card> returnedCards = {card};

    EXPECT_CALL(mock, callAddCardToHand(_, _))
    .Times(1)
    .WillOnce([](Player* player, Card card){
        player->addCardToHand(card);
    });

    EXPECT_CALL(mock, callGetHand(_))
    .Times(2)
    .WillOnce(Return(returnedCards))
    .WillOnce(Return(returnedCards));

    EXPECT_CALL(mock, callRemovePlayedCard(_))
    .Times(1);

    EXPECT_CALL(mock, callGetDeck(_))
    .Times(1)
    .WillOnce(Return(validDeck));

    playGame.dealToPlayer(&mock, 0);

    string text = buffer.str();
    cout.rdbuf(prevcoutbuf);

    EXPECT_EQ("\t\tPlayer 1 has been dealt a ace of heart\n\n", text);
}

TEST(HandManagement_DealToPlayerShould, DecreaseTheDeckSizeByOneForOnePlayer) {
    MockGame mock;
    PlayGame playGame;
    Card card("heart", "one");
    vector<Card> returnedCards = {card};
    Card validCardForBackOfDeck("valid", "valid"); 
    vector<Card> validDeck = {validCardForBackOfDeck};
    vector<int> deckVector = {1, 1, 1};
    Player* player = new Player();
    vector<Player*> players = {player};
    playGame.setPlayerList(players);

    EXPECT_CALL(mock, callGetHand(_))
    .Times(2)
    .WillOnce(Return(returnedCards))
    .WillOnce(Return(returnedCards));

    EXPECT_CALL(mock, callRemovePlayedCard( _))
    .Times(1)
    .WillOnce([&deckVector](Deck deck){
        deckVector.pop_back();
    });

    EXPECT_CALL(mock, callGetDeck(_))
    .Times(1)
    .WillOnce(Return(validDeck));

    playGame.dealToPlayer(&mock, 0);


    EXPECT_EQ(deckVector.size(), 2);
}



TEST(HandManagement_GetTotalHandShould, ReturnZeroForNoneInHand) {
    MockGame mock;
    PlayGame playGame;
    vector<Card> hand = {};
    
    EXPECT_CALL(mock, callGetCardTrueValue(_))
    .Times(0);

    EXPECT_EQ(playGame.getTotalHand(&mock, hand), 0);
}

TEST(HandManagement_GetTotalHandShould, ReturnTwentyForTwoTensInHand) {
    MockGame mock;
    PlayGame playGame;
    vector<Card> hand = {};
    Card cardHearts("hearts", "ten");
    hand.push_back(cardHearts);
    Card cardSpades("spades", "jack");
    hand.push_back(cardSpades);

    EXPECT_CALL(mock, callGetCardTrueValue(_))
    .Times(2)
    .WillRepeatedly(Return(10));

    EXPECT_EQ(playGame.getTotalHand(&mock, hand), 20);
}

TEST(HandManagement_GetTotalHandShould, Return20GivenNineAndAce) {
    MockGame mock;
    PlayGame playGame;
    vector<Card> hand = {};
    Card cardHearts("hearts", "nine");
    hand.push_back(cardHearts);
    Card cardSpades("spades", "ace");
    hand.push_back(cardSpades);

    EXPECT_CALL(mock, callGetCardTrueValue(_))
    .Times(1)
    .WillOnce(Return(9));

    EXPECT_EQ(playGame.getTotalHand(&mock, hand, 11), 20);
}

TEST(HandManagement_GetTotalHandShould, ReturnTenGivenNineAndAce) {
    MockGame mock;
    PlayGame playGame;
    vector<Card> hand = {};
    Card cardHearts("hearts", "nine");
    hand.push_back(cardHearts);
    Card cardSpades("spades", "ace");
    hand.push_back(cardSpades);

    EXPECT_CALL(mock, callGetCardTrueValue(_))
    .Times(2)
    .WillOnce(Return(1))
    .WillOnce(Return(9));

    EXPECT_EQ(playGame.getTotalHand(&mock, hand, 1), 10);
}

TEST(HandManagement_GetTotalHandShould, Return13GivenThreeAces) {
    MockGame mock;
    PlayGame playGame;
    vector<Card> hand = {};
    Card cardHearts("hearts", "ace");
    hand.push_back(cardHearts);
    Card cardSpades("spades", "ace");
    hand.push_back(cardSpades);
    Card cardClubs("clubs", "ace");
    hand.push_back(cardClubs);

    EXPECT_CALL(mock, callGetCardTrueValue(_))
    .Times(2)
    .WillOnce(Return(1))
    .WillOnce(Return(1));

    EXPECT_EQ(playGame.getTotalHand(&mock, hand, 11), 13);
}



TEST(HandManagement_GetDeckShould, ReturnADeckOfSize52AfterInitialisation) {
    PlayGame playGame;
    Deck deck;
    deck.init();
    EXPECT_EQ(deck.getDeck().size(), 52);
} 

TEST(HandManagement_GetDeckShould, ReturnADeckOfSize52BeforeInitialisation) {
    PlayGame playGame;
    Deck deck;
    EXPECT_EQ(deck.getDeck().size(), 0);
} 