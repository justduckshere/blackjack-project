#include <gtest/gtest.h>
#include "player.h"
#include <sstream>

using namespace std;

TEST(PlayerGetHandShould, ReturnZeroOnInitialisation) {
  Player player;
  EXPECT_EQ(player.getHand().size(), 0);
}

TEST(PlayerGetCurrentTotalShould, ReturnZeroOnInitialisation){
  Player player;
  EXPECT_EQ(player.getCurrentTotal(), 0);
}


TEST(PlayerAddCardToHandShould, IncreaseTheHandSizeByOne){
  Player player;
  Card card("hearts", "one");
  player.addCardToHand(card);
  ASSERT_TRUE(player.getHand().size() == 1);
}

TEST(PlayerAddCardToHandShould, HaveHandWithThatCardOnly){
  Player player;
  Card card("hearts", "one");
  player.addCardToHand(card);
  ASSERT_TRUE(player.getHand()[0].getValue() == card.getValue());
  ASSERT_TRUE(player.getHand()[0].getSuit() == card.getSuit());
}


TEST(PlayerGetPlayerHasGoneBustShould, ReturnFalseOnInitialisedPlayer) {
  Player player;
  EXPECT_EQ(player.getPlayerHasGoneBust(), false);
}


TEST(PlayerSetPlayerHasGoneBustShould, SetTheBoolToTrue) {
  Player player;
  player.setPlayerHasGoneBust();
  EXPECT_EQ(player.getPlayerHasGoneBust(), true);
}


TEST(PlayerSetCurrentTotalShould, SetCurrentTotalToTheInputValue) {
  Player player;
  player.setCurrentTotal(12);
  EXPECT_EQ(player.getCurrentTotal(), 12);
}


TEST(PlayerDisplayHandShould, DisplaySimpleHandAsExpected) {
  stringstream buffer;
  streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf());
  Player player;    
  Card card("hearts", "ace");
  player.addCardToHand(card);
  
  player.displayHand();

  string text = buffer.str();
  cout.rdbuf(prevcoutbuf);

  EXPECT_EQ(text,"a ace of hearts\n\n");
}

TEST(PlayerDisplayHandShould, DisplayComplexHandAsExpected) {
  stringstream buffer;
  streambuf* prevcoutbuf = cout.rdbuf(buffer.rdbuf());
  Player player;    
  Card card("hearts", "ace");
  player.addCardToHand(card);
  Card cardTwo("hearts", "two");
  player.addCardToHand(cardTwo);

  
  player.displayHand();

  string text = buffer.str();
  cout.rdbuf(prevcoutbuf);

  EXPECT_EQ(text,"a two of hearts, a ace of hearts\n\n");
}