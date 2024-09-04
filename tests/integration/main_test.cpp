#include <gtest/gtest.h>
#include <gmock/gmock.h>

int main(int argc, char ** argv) {
    ::testing::FLAGS_gmock_verbose = "error"; // prevents warnings in print assertions
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}