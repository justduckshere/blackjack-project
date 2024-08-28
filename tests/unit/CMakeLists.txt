include(AddGoogleTest)

add_executable(
    unit_tests
    card_test.cpp
    dealerlogic_test.cpp
    deck_test.cpp
    gamelogic_test.cpp
    handmanagement_test.cpp
    main_test.cpp
    player_test.cpp
    playerlogic_test.cpp
    playgame_test.cpp
    winnerhandler_test.cpp
)

find_package(GTest REQUIRED)

target_link_libraries(
    unit_tests
    blackjack
    GTest::gtest_main
    GTest::gmock_main
)

include(GoogleTest) 
gtest_discover_tests(unit_tests)