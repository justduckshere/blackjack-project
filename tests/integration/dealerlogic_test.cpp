#include <gtest/gtest.h>
#include "game/playgame.h"
#include <sstream>

TEST(DealerLogic_PlayDealersRoundShould, NotIncreaseHandSizeForHandLargerThan17WithAce) {
    PlayGame playGame;
    PlayGameWrapper* wrapper = new PlayGame();
    Player* dealer = new Player();
    Card cardHearts("hearts", "seven");
    dealer->addCardToHand(cardHearts);
    Card cardSpades("spades", "ace");
    dealer->addCardToHand(cardSpades);
    playGame.setDealer(dealer);
    
    playGame.playDealersRound(wrapper);

    EXPECT_EQ(playGame.getDealer()->getHand().size(), 2);
}

TEST(DealerLogic_PlayDealersRoundShould, NotIncreaseHandSizeForHandLargerThan17WithoutAce) {
    PlayGame playGame;
    PlayGameWrapper* wrapper = new PlayGame();
    Player* dealer = new Player();
    Card cardHearts("hearts", "seven");
    dealer->addCardToHand(cardHearts);
    Card cardSpades("spades", "jack");
    dealer->addCardToHand(cardSpades);

    playGame.setDealer(dealer);
    playGame.playDealersRound(wrapper);

    EXPECT_EQ(playGame.getDealer()->getHand().size(), 2);
}

TEST(DealerLogic_PlayDealersRoundShould, IncreaseHandSizeForHandLessThan17WithAce) {
    PlayGame playGame;
    Player* dealer = new Player();
    PlayGameWrapper* wrapper = new PlayGame();
    Deck deck;
    deck.init();
    Card cardHearts("hearts", "two");
    dealer->addCardToHand(cardHearts);
    Card cardSpades("spades", "ace");
    dealer->addCardToHand(cardSpades);

    playGame.setDealer(dealer);
    playGame.playDealersRound(wrapper);

    EXPECT_EQ(playGame.getDealer()->getHand().size(),3);
}

TEST(DealerLogic_PlayDealersRoundShould, IncreaseHandSizeForHandLessThan17WithoutAce) {
    PlayGame playGame;
    Player* dealer = new Player();
    PlayGameWrapper* wrapper = new PlayGame();
    Deck deck;
    deck.init();
    Card cardHearts("hearts", "two");
    dealer->addCardToHand(cardHearts);
    Card cardSpades("spades", "two");
    dealer->addCardToHand(cardSpades);

    playGame.setDealer(dealer);
    playGame.playDealersRound(wrapper);

    EXPECT_EQ(playGame.getDealer()->getHand().size(),3);
}

TEST(DealerLogic_PlayDealersRoundShould, DecreaseTheDeckSizeBy1ForHandLessThan17) {
    PlayGame playGame;
    Player* dealer = new Player();
    PlayGameWrapper* wrapper = new PlayGame();
    Deck deck;
    deck.init();
    Card cardHearts("hearts", "two");
    dealer->addCardToHand(cardHearts);
    Card cardSpades("spades", "two");
    dealer->addCardToHand(cardSpades);

    playGame.setDealer(dealer);
    playGame.playDealersRound(wrapper);

    EXPECT_EQ(deck.getDeck().size(),51);
}

TEST(DealerLogic_PlayDealersRoundShould, NotDecreaseTheDeckSizeByForHandGreaterThan17) {
    PlayGame playGame;
    Player* dealer = new Player();
    PlayGameWrapper* wrapper = new PlayGame();
    Deck deck;
    deck.init();
    Card cardHearts("hearts", "ten");
    dealer->addCardToHand(cardHearts);
    Card cardSpades("spades", "ten");
    dealer->addCardToHand(cardSpades);

    playGame.setDealer(dealer);
    playGame.playDealersRound(wrapper);

    EXPECT_EQ(deck.getDeck().size(),52);
}


TEST(DealerLogic_DetermineIfDealerShouldDrawShould, ReturnTrueIfDealerHasLessThan16TotalWithNoAce) {
    PlayGame playGame;
    Player* dealer = new Player();
    PlayGameWrapper* wrapper = new PlayGame();
    Card cardHearts("hearts", "nine");
    dealer->addCardToHand(cardHearts);
    Card cardSpades("spades", "two");
    dealer->addCardToHand(cardSpades);

    playGame.setDealer(dealer);

    EXPECT_EQ(playGame.determineIfDealerShouldDraw(wrapper, false), true);
}

TEST(DealerLogic_DetermineIfDealerShouldDrawShould, ReturnTrueIfDealerHasLessThan16InTotalWithAce) {
    PlayGame playGame;
    Player* dealer = new Player();
    PlayGameWrapper* wrapper = new PlayGame();
    Card cardHearts("hearts", "two");
    dealer->addCardToHand(cardHearts);
    Card cardSpades("spades", "ace");
    dealer->addCardToHand(cardSpades);

    playGame.setDealer(dealer);

    EXPECT_EQ(playGame.determineIfDealerShouldDraw(wrapper, true), true);
}

TEST(DealerLogic_DetermineIfDealerShouldDrawShould, ReturnFalseIfDealerHasMoreThan16InTotalWithNoAce) {
    PlayGame playGame;
    Player* dealer = new Player();
    PlayGameWrapper* wrapper = new PlayGame();
    Card cardHearts("hearts", "nine");
    dealer->addCardToHand(cardHearts);
    Card cardSpades("spades", "nine");
    dealer->addCardToHand(cardSpades);

    playGame.setDealer(dealer);

    EXPECT_EQ(playGame.determineIfDealerShouldDraw(wrapper, false), false);
}

TEST(DealerLogic_DetermineIfDealerShouldDrawShould, ReturnFalseIfDealerHasMoreThan16InTotalWithAce) {
    PlayGame playGame;
    Player* dealer = new Player();
    PlayGameWrapper* wrapper = new PlayGame();
    Card cardHearts("hearts", "nine");
    dealer->addCardToHand(cardHearts);
    Card cardSpades("spades", "ace");
    dealer->addCardToHand(cardSpades);

    playGame.setDealer(dealer);

    EXPECT_EQ(playGame.determineIfDealerShouldDraw(wrapper, true), false);
}



TEST(DealerLogic_GetDealerShould, GetTheDealerAccordingToInput) {
    PlayGame playGame;
    Player* dealer = new Player();
    Card cardHearts("hearts", "ten");
    dealer->addCardToHand(cardHearts);

    playGame.setDealer(dealer);

    EXPECT_EQ(playGame.getDealer()->getHand()[0].getSuit(), "hearts");
    EXPECT_EQ(playGame.getDealer()->getHand()[0].getValue(), "ten");

}