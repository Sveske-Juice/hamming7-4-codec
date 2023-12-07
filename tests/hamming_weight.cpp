#include <catch2/catch_test_macros.hpp>
#include <cstdint>

#include "hamming_functions.h"

TEST_CASE( "Hamming Weights Computed", "[hamming weight]" ) {
    REQUIRE(hamming_weight(0) == 0);
    REQUIRE(hamming_weight(1) == 1);
    REQUIRE(hamming_weight(2) == 1);
    REQUIRE(hamming_weight(3) == 2);
    REQUIRE(hamming_weight(4) == 1);
    REQUIRE(hamming_weight(5) == 2);
    REQUIRE(hamming_weight(6) == 2);
    REQUIRE(hamming_weight(7) == 3);
    REQUIRE(hamming_weight(8) == 1);
    REQUIRE(hamming_weight(9) == 2);
    REQUIRE(hamming_weight(10) == 2);

    REQUIRE(hamming_weight(0b11111111) == 8);

    // Testing multiple bytes
    uint8_t cw1[] = { 0, 0 };
    REQUIRE(hamming_weight(cw1, 2) == 0);

    uint8_t cw2[] = { 0b11111111, 0b11111111 };
    REQUIRE(hamming_weight(cw2, 2) == 16);

    uint8_t cw3[] = { 0, 0b11111111 };
    REQUIRE(hamming_weight(cw3, 2) == 8);
}
