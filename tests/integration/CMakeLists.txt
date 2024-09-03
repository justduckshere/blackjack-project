include(AddGoogleTest)
add_executable(
    int_tests
    dealerlogic_test.cpp
    gamelogic_test.cpp
    # winnerhandler_test.cpp
    # handmanagement_test.cpp
    # playerlogic_test.cpp
    main_test.cpp
)

find_package(GTest REQUIRED)

target_link_libraries(
    int_tests
    blackjack
    GTest::gtest_main
    GTest::gmock_main
)

include(GoogleTest) 
gtest_discover_tests(int_tests)
