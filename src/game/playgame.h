#ifndef PLAYGAME_H
#define PLAYGAME_H

#include "../player/player.h"
#include "../hand/deck.h"
#include "../hand/card.h"
#include "../hand/deck.h"
#include <vector>

using namespace std; 

class PlayGameWrapper {
public:
    virtual int getUserIntResponse() = 0;
    virtual vector<Card> callGetDeck(Deck inputDeck) = 0;
    virtual int callGetCardTrueValue(Card card) = 0;
    virtual vector<Card> callGetHand(Player* player) =0;
    virtual void callRemovePlayedCard(Deck deck) = 0;
    virtual void callDealToPlayer(PlayGameWrapper* wrapper, int playerNumber) = 0;
    
    virtual void callAddCardToHand(Player* player, Card card) = 0;
    virtual int callGetTotalHand(PlayGameWrapper* wrapper, vector<Card> hand) = 0;
    virtual int callGetTotalHand(PlayGameWrapper* wrapper, vector<Card> hand, int aceValue) =  0;
    virtual void callDisplayHand(Player* player) =  0;

    virtual bool callGetPlayerHasGoneBust(Player* player) =0;
    virtual int callGetCurrentTotal(Player* player) = 0;
    virtual std::pair<int, vector<int>> callGetListOfPlayersWithHighestScores(PlayGameWrapper* wrapper) =0;
    virtual void callDisplayWin(bool dealerHasWon, vector<int> playersWhoHaveWon, int score) = 0;
    
    virtual bool callHandHasGoneBust(PlayGameWrapper* wrapper, vector<Card> hand) =  0;
    virtual bool callDetermineIfDealerShouldDraw(PlayGameWrapper* wrapper, bool hasAce) = 0;
    virtual bool callHandHasAce(vector<Card> hand) = 0;
    virtual bool callHandis21(PlayGameWrapper* wrapper, vector<Card> hand) = 0;
    virtual bool callHandHasWon(PlayGameWrapper *wrapper, vector<Card> hand) =0 ;
    virtual bool callHandHasWonWithAce(PlayGameWrapper *wrapper, vector<Card> hand, int aceValue) =0;
    virtual vector<int> callReturnListOfPlayersAt21(PlayGameWrapper *wrapper) = 0;
    virtual void callDetermineWinnerFromNobody21(PlayGameWrapper *wrapper) = 0;
    virtual void callPlayDealersRound(PlayGameWrapper* wrapper) = 0;
    virtual bool callAllPlayersHaveGoneBust(PlayGameWrapper* wrapper) = 0;
    
    virtual void callInit(Deck deck) = 0;
    virtual void callShuffle(Deck deck) =0;
    virtual void callCreatePlayerList(PlayGameWrapper *wrapper) =0;
    virtual void callDealToEveryone(PlayGameWrapper *wrapper) =0;
    virtual void callSetHighestValidHandValueForPlayer(PlayGameWrapper *wrapper, Player* dealerPlayer) =0;
    virtual void callInitialiseGame(PlayGameWrapper *wrapper) =0;
    virtual Player* callGetDealer() = 0;
    virtual bool callRegularGamePlay(PlayGameWrapper *wrapper) = 0;

   
};

class PlayGame : public PlayGameWrapper{
public:
    // regular gameplay functions 
    void playGame(PlayGameWrapper* wrapper);
    void initialiseGame(PlayGameWrapper* wrapper);
    bool regularGamePlay(PlayGameWrapper *wrapper);

    // dealer-specific functions 
    void playDealersRound(PlayGameWrapper* wrapper);
    bool determineIfDealerShouldDraw(PlayGameWrapper* wrapper, bool hasAce);
    void setDealer(Player* dealer);
    Player* getDealer();

    //player-specific functions
    void playPlayersRound(PlayGameWrapper* wrapper);
    vector<Player*> getPlayerList();
    void setPlayerList(vector<Player*> players);
    void createPlayerList(PlayGameWrapper* wrapper);

    // hand management functions 
    void dealToEveryone(PlayGameWrapper *wrapper);
    void dealToPlayer(PlayGameWrapper* wrapper, int playerNumber);
    Deck getDeck();
    void setCurrentDeck(Deck deck);
    int getTotalHand(PlayGameWrapper *playGameWrapper, vector<Card> hand);
    int getTotalHand(PlayGameWrapper *playGameWrapper, vector<Card> hand, int aceValue);

    // Game logic functions 
    bool handHasGoneBust(PlayGameWrapper *wrapper, vector<Card> hand);
    bool handis21(PlayGameWrapper *playGameWrapper, vector<Card> hand);
    bool handHasAce(vector<Card> hand);
    bool handHasWon(PlayGameWrapper *playGameWrapper,vector<Card> hand);
    bool handHasWon(PlayGameWrapper *playGameWrapper,vector<Card> hand, int aceValue);
    vector<int> returnListOfPlayersAt21(PlayGameWrapper *wrapper);
    bool allPlayersHaveGoneBust(PlayGameWrapper *wrapper);


    // functions for handling winning
    void displayWin(bool dealerHasWon, vector<int> playersWhoHaveWon, int score);
    void determineWinnerFromNobody21(PlayGameWrapper *wrapper);
    void setHighestValidHandValueForPlayer(PlayGameWrapper *wrapper, Player* player);
    pair<int, vector<int>> getListOfPlayersWithHighestScores(PlayGameWrapper *wrapper);

    
    
    ///// implementations for wrappers
    int getUserIntResponse() override;
    vector<Card> callGetDeck(Deck inputDeck) override;
    int callGetCardTrueValue(Card card) override;
    vector<Card> callGetHand(Player* player) override;
    void callRemovePlayedCard(Deck deck) override;
    void callDealToPlayer(PlayGameWrapper* wrapper, int playerNumber) override;
    
    void callAddCardToHand(Player* player, Card card) override;
    int callGetTotalHand(PlayGameWrapper* wrapper, vector<Card> hand) override;
    int callGetTotalHand(PlayGameWrapper* wrapper, vector<Card> hand, int aceValue) override;
    void callDisplayHand(Player* player) override;

    bool callGetPlayerHasGoneBust(Player* player) override;
    int callGetCurrentTotal(Player* player) override;
    std::pair<int, vector<int>> callGetListOfPlayersWithHighestScores(PlayGameWrapper* wrapper) override;
    void callDisplayWin(bool dealerHasWon, vector<int> playersWhoHaveWon, int score) override;
    
    bool callHandHasGoneBust(PlayGameWrapper* wrapper, vector<Card> hand) override;
    bool callDetermineIfDealerShouldDraw(PlayGameWrapper* wrapper, bool hasAce) override;
    bool callHandHasAce(vector<Card> hand) override;
    bool callHandis21(PlayGameWrapper* wrapper, vector<Card> hand) override;
    bool callHandHasWon(PlayGameWrapper *wrapper, vector<Card> hand) override;
    bool callHandHasWonWithAce(PlayGameWrapper *wrapper, vector<Card> hand, int aceValue) override;
    vector<int> callReturnListOfPlayersAt21(PlayGameWrapper *wrapper) override;
    void callDetermineWinnerFromNobody21(PlayGameWrapper *wrapper) override;
    void callPlayDealersRound(PlayGameWrapper* wrapper) override;
    bool callAllPlayersHaveGoneBust(PlayGameWrapper* wrapper) override;
    
    void callInit(Deck deck) override;
    void callShuffle(Deck deck) override;
    void callCreatePlayerList(PlayGameWrapper *wrapper) override;
    void callDealToEveryone(PlayGameWrapper *wrapper) override;
    void callSetHighestValidHandValueForPlayer(PlayGameWrapper *wrapper, Player* dealerPlayer) override;
    void callInitialiseGame(PlayGameWrapper *wrapper) override;
    Player* callGetDealer() override;
    bool callRegularGamePlay(PlayGameWrapper *wrapper) override;

private: 
    static vector<Player*> playerList;
    static Deck currentDeck;
    static Player* dealer;

};



#endif
