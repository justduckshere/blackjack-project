#include <gtest/gtest.h>
#include "game/playgame.h"
#include <sstream>


TEST(PlayDealersRoundShould, PrintOutTheDealersLatestDealtCard) {
    stringstream buffer;
    streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf());
    PlayGame playGame;
    Player* dealer = new Player();
    Card cardHearts("hearts", "ten");
    dealer->addCardToHand(cardHearts);
    playGame.setDealer(dealer);


    playGame.playDealersRound();
    string text = buffer.str();
    cout.rdbuf(prevcoutbuf);
    EXPECT_EQ("Dealers second card is: ten of hearts\n\n", text);
}

TEST(PlayDealersRoundShould, NotIncreaseHandSizeForHandLargerThan17WithAce) {
    PlayGame playGame;
    Player* dealer = new Player();
    Card cardHearts("hearts", "seven");
    dealer->addCardToHand(cardHearts);
    Card cardSpades("spades", "ace");
    dealer->addCardToHand(cardSpades);

    playGame.setDealer(dealer);
    playGame.playDealersRound();

    EXPECT_EQ(playGame.getDealer()->getHand().size(), 2);
}

TEST(PlayDealersRoundShould, NotIncreaseHandSizeForHandLargerThan17WithoutAce) {
    PlayGame playGame;
    Player* dealer = new Player();
    Card cardHearts("hearts", "seven");
    dealer->addCardToHand(cardHearts);
    Card cardSpades("spades", "jack");
    dealer->addCardToHand(cardSpades);

    playGame.setDealer(dealer);
    playGame.playDealersRound();

    EXPECT_EQ(playGame.getDealer()->getHand().size(), 2);
}

TEST(PlayDealersRoundShould, IncreaseHandSizeForHandLessThan17WithAce) {
    PlayGame playGame;
    Player* dealer = new Player();
    Card cardHearts("hearts", "two");
    dealer->addCardToHand(cardHearts);
    Card cardSpades("spades", "ace");
    dealer->addCardToHand(cardSpades);

    playGame.setDealer(dealer);
    playGame.playDealersRound();

    EXPECT_EQ(playGame.getDealer()->getHand().size(),3);
}

TEST(PlayDealersRoundShould, IncreaseHandSizeForHandLessThan17WithoutAce) {
    PlayGame playGame;
    Player* dealer = new Player();
    Card cardHearts("hearts", "two");
    dealer->addCardToHand(cardHearts);
    Card cardSpades("spades", "two");
    dealer->addCardToHand(cardSpades);

    playGame.setDealer(dealer);
    playGame.playDealersRound();

    EXPECT_EQ(playGame.getDealer()->getHand().size(),3);
}



TEST(DetermineIfDealerShouldDrawShould, ReturnTrueIfDealerHasLessThan16Total) {
    PlayGame playGame;
    Player* dealer = new Player();
    Card cardHearts("hearts", "nine");
    dealer->addCardToHand(cardHearts);
    Card cardSpades("spades", "two");
    dealer->addCardToHand(cardSpades);

    playGame.setDealer(dealer);

    EXPECT_EQ(playGame.determineIfDealerShouldDraw(false), true);
}

TEST(DetermineIfDealerShouldDrawShould, ReturnFalseIfDealerHasMoreThan16InTotalWithNoAce) {
    PlayGame playGame;
    Player* dealer = new Player();
    Card cardHearts("hearts", "nine");
    dealer->addCardToHand(cardHearts);
    Card cardSpades("spades", "nine");
    dealer->addCardToHand(cardSpades);

    playGame.setDealer(dealer);

    EXPECT_EQ(playGame.determineIfDealerShouldDraw(false), false);
}


TEST(DetermineIfDealerShouldDrawShould, ReturnFalseIfDealerHasMoreThan16InTotalWithAnAce) {
    PlayGame playGame;
    Player* dealer = new Player();
    Card cardHearts("hearts", "nine");
    dealer->addCardToHand(cardHearts);
    Card cardSpades("spades", "ace");
    dealer->addCardToHand(cardSpades);

    playGame.setDealer(dealer);

    EXPECT_EQ(playGame.determineIfDealerShouldDraw(true), false);
}

TEST(DetermineIfDealerShouldDrawShould, ReturnTrueIfDealerHasLessThan16InTotalWithAnAce) {
    PlayGame playGame;
    Player* dealer = new Player();
    Card cardHearts("hearts", "two");
    dealer->addCardToHand(cardHearts);
    Card cardSpades("spades", "ace");
    dealer->addCardToHand(cardSpades);

    playGame.setDealer(dealer);

    EXPECT_EQ(playGame.determineIfDealerShouldDraw(true), true);
}


TEST(GetDealerShould, ReturnANotNilPointerOnInitialisation) {
    PlayGame playGame;
    Player* dealer = playGame.getDealer();
    ASSERT_TRUE(dealer != nullptr);
}

TEST(SetDealerShould, SetTheDealerAccordingToInput) {
    PlayGame playGame;
    Player* dealer = new Player();
    Card cardHearts("hearts", "ten");
    dealer->addCardToHand(cardHearts);

    playGame.setDealer(dealer);

    EXPECT_EQ(playGame.getDealer()->getHand()[0].getSuit(), "hearts");
    EXPECT_EQ(playGame.getDealer()->getHand()[0].getValue(), "ten");

}