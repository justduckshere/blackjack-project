#include "playgame.h"

int PlayGame::callGetCardTrueValue(Card card){
    return card.getCardTrueValue();
}

vector<Card> PlayGame::callGetDeck(Deck inputDeck) {
    return inputDeck.getDeck();
}

vector<Card> PlayGame::callGetHand(Player* player){
    return player->getHand();
}

void PlayGame::callAddCardToHand(Player* player, Card card){
    player->addCardToHand(card);
}

void PlayGame::callRemovePlayedCard(Deck deck) {
    deck.removePlayedCard();
}

void PlayGame::callDealToPlayer(PlayGameWrapper* wrapper, int playerNumber){
    dealToPlayer(wrapper,playerNumber);
}

int PlayGame::callGetTotalHand(PlayGameWrapper* wrapper, vector<Card> hand){
    return getTotalHand(wrapper, hand);
}

int PlayGame::callGetTotalHand(PlayGameWrapper* wrapper, vector<Card> hand, int aceValue){
    return getTotalHand(wrapper, hand, aceValue);
}

bool PlayGame::callDetermineIfDealerShouldDraw(PlayGameWrapper* wrapper, bool hasAce) {
    return determineIfDealerShouldDraw(wrapper, hasAce);
}

bool PlayGame::callHandHasAce(vector<Card> hand) {
    return handHasAce(hand);
}

bool PlayGame::callGetPlayerHasGoneBust(Player* player){
    return player->getPlayerHasGoneBust();
}

void PlayGame::callDisplayHand(Player* player){
    player->displayHand();
}
bool PlayGame::callHandHasGoneBust(PlayGameWrapper* wrapper, vector<Card> hand) {
    return handHasGoneBust(wrapper, hand);
}

int PlayGame::callGetCurrentTotal(Player* player) {
    return player->getCurrentTotal();
}

std::pair<int, vector<int>> PlayGame::callGetListOfPlayersWithHighestScores(PlayGameWrapper* wrapper){
    return getListOfPlayersWithHighestScores(wrapper);
}

void PlayGame::callDisplayWin(bool dealerHasWon, vector<int> playersWhoHaveWon, int score){
    return displayWin(dealerHasWon, playersWhoHaveWon, score);
}

bool PlayGame::callHandis21(PlayGameWrapper* wrapper, vector<Card> hand) {
    return handis21(wrapper, hand);
}

bool PlayGame::callHandHasWon(PlayGameWrapper *wrapper, vector<Card> hand){
    return handHasWon(wrapper, hand);
}
bool PlayGame::callHandHasWonWithAce(PlayGameWrapper *wrapper, vector<Card> hand, int aceValue) {
    return handHasWon(wrapper, hand, aceValue);
}

vector<int> PlayGame::callReturnListOfPlayersAt21(PlayGameWrapper *wrapper) {
    return returnListOfPlayersAt21(wrapper);
}

void PlayGame::callDetermineWinnerFromNobody21(PlayGameWrapper *wrapper) {
    determineWinnerFromNobody21(wrapper);
}

void PlayGame::callPlayDealersRound(PlayGameWrapper* wrapper) {
    playDealersRound(wrapper);
}

bool PlayGame::callAllPlayersHaveGoneBust(PlayGameWrapper* wrapper) {
    return allPlayersHaveGoneBust(wrapper);
}

void PlayGame::callInit(Deck deck) {
    deck.init();
}

void PlayGame::callShuffle(Deck deck) {
    deck.shuffle();
}

void PlayGame::callCreatePlayerList(PlayGameWrapper *wrapper) {
    createPlayerList(wrapper);
}

void PlayGame::callDealToEveryone(PlayGameWrapper *wrapper){
    dealToEveryone(wrapper);
}


void PlayGame::callSetHighestValidHandValueForPlayer(PlayGameWrapper *wrapper, Player* dealerPlayer) {
    setHighestValidHandValueForPlayer(wrapper, dealerPlayer);
}

void PlayGame::callInitialiseGame(PlayGameWrapper *wrapper) {
    initialiseGame(wrapper);
}

Player* PlayGame::callGetDealer() {
    return getDealer();
}

bool PlayGame::callRegularGamePlay(PlayGameWrapper *wrapper) {
    return regularGamePlay(wrapper);
}