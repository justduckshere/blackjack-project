#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "game/playgame.h"
#include "hand/card.h"
#include "hand/deck.h"
#include "player/player.h"
#include <vector>
#include <utility>


class MockGame :  public PlayGameWrapper{
public:
    MOCK_METHOD(int, callGetTotalHand, (PlayGameWrapper* wrapper, vector<Card> hand), (override));
    MOCK_METHOD(int, callGetTotalHand, (PlayGameWrapper* wrapper, vector<Card> hand, int aceValue), (override));
    MOCK_METHOD(bool, callDetermineIfDealerShouldDraw, (PlayGameWrapper* wrapper, bool hasAce), (override));
    MOCK_METHOD(bool, callCheckIfHandHasAce, (vector<Card> hand), (override));
    MOCK_METHOD(vector<Card>, callGetDeck, (Deck inputDeck), (override));

    MOCK_METHOD(int, callGetCardTrueValue, (Card card), (override));
    MOCK_METHOD(int, getUserIntResponse, (), (override));
    MOCK_METHOD(vector<Card>, callGetHand, (Player* player), (override));
    MOCK_METHOD(void, callAddCardToHand, (Player* player, Card card), (override));
    MOCK_METHOD(void, callRemovePlayedCard, (Deck deck), (override));
    MOCK_METHOD(void, callDealToPlayer, (PlayGameWrapper* wrapper, int playerNumber), (override));

    MOCK_METHOD(bool, callGetPlayerHasGoneBust, (Player* player), (override));
    MOCK_METHOD(void, callDisplayHand, (Player* player), (override));
    MOCK_METHOD(bool, callCheckIfHandHasGoneBust, (PlayGameWrapper* wrapper, vector<Card> hand), (override));

    MOCK_METHOD(int, callGetCurrentTotal, (Player* player), (override));
    MOCK_METHOD((std::pair<int, vector<int>>), callGetListOfPlayersWithHighestScores, (PlayGameWrapper* wrapper), (override));
    MOCK_METHOD(void, callDisplayWin, (bool dealerHasWon, vector<int> playersWhoHaveWon, int score), (override));
    MOCK_METHOD(bool, callVerifyHandHasWon, (PlayGameWrapper* wrapper, vector<Card> hand), (override));
    MOCK_METHOD(bool, callCheckIfHandHasWon, (PlayGameWrapper *wrapper, vector<Card> hand), (override));
    MOCK_METHOD(bool, callCheckIfHandHasWonWithAce, (PlayGameWrapper *wrapper, vector<Card> hand, int aceValue), (override));

    MOCK_METHOD(vector<int>, callReturnListOfPlayersAt21, (PlayGameWrapper* wrapper), (override));
    MOCK_METHOD(void, callDetermineWinnerFromNobody21, (PlayGameWrapper* wrapper), (override));
    MOCK_METHOD(void, callPlayDealersRound, (PlayGameWrapper* wrapper), (override));
    MOCK_METHOD(bool, callCheckIfAllPlayersHaveGoneBust, (PlayGameWrapper* wrapper), (override));
    MOCK_METHOD(void, callInit, (Deck deck), (override));
    MOCK_METHOD(void, callShuffle, (Deck deck), (override));
    MOCK_METHOD(void, callCreatePlayerList, (PlayGameWrapper *wrapper), (override));
    MOCK_METHOD(void, callDealToEveryone, (PlayGameWrapper *wrapper), (override));
    MOCK_METHOD(void, callSetHighestValidHandValueForPlayer, (PlayGameWrapper *wrapper, Player* dealerPlayer), (override));
    MOCK_METHOD(void, callInitialiseGame, (PlayGameWrapper *wrapper), (override));
    MOCK_METHOD(Player*, callGetDealer, (), (override));
    MOCK_METHOD(bool, callRegularGamePlay, (PlayGameWrapper *wrapper), (override));

};