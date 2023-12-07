#include <catch2/catch_test_macros.hpp>

#include "hamming_functions.h"

TEST_CASE( "Hamming Distances Computed", "[hamming distance]" ) {
    uint8_t cw1_1 = 0;
    uint8_t cw1_2 = 0;
    REQUIRE(hamming_distance(&cw1_1, &cw1_2, 1) == 0);

    uint8_t cw2_1 = 0b11111111;
    uint8_t cw2_2 = 0;
    REQUIRE(hamming_distance(&cw2_1, &cw2_2, 1) == 8);

    uint8_t cw3_1 = 0b00111;
    uint8_t cw3_2 = 0b00110;
    REQUIRE(hamming_distance(&cw3_1, &cw3_2, 1) == 1);

    // Testing multiple bytes
    uint8_t cw4_1[] = {0, 5};
    uint8_t cw4_2[] = {0, 5};
    REQUIRE(hamming_distance(cw4_1, cw4_2, 2) == 0);

    uint8_t cw5_1[] = {0, 0};
    uint8_t cw5_2[] = {0b11111111, 0b11111111};
    REQUIRE(hamming_distance(cw5_1, cw5_2, 2) == 16);

    // Check if 0b0011 is the same as 0b11 (they should be)
    uint8_t cw6_1[] = {0b11100100, 0b0011};
    uint8_t cw6_2[] = {0b00100010, 0b11};
    REQUIRE(hamming_distance(cw6_1, cw6_2, 2) == 4);

    uint8_t cw7_1[] = {0b11100100, 0b1100};
    uint8_t cw7_2[] = {0b00100010, 0b11};
    REQUIRE(hamming_distance(cw7_1, cw7_2, 2) == 8);
}
