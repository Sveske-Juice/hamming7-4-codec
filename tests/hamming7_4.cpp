#include <catch2/catch_test_macros.hpp>
#include <cstdint>

#include "hamming7_4.h"

TEST_CASE("Hamming (7,4) Encoding", "[hamming (7,4) encode]") {
    // Encode tests
    REQUIRE(encode_hamming7_4(0b0101) == 0b01001010);
    REQUIRE(encode_hamming7_4(0b1111) == 0b11111110);
    REQUIRE(encode_hamming7_4(0) == 0);

    // More byte tests
    uint8_t c1[] = {0, 0b1111, 0b0101};
    uint8_t outBuffer1[6] = {0};
    uint8_t correctCW1[] = {0, 0, 0b11111110, 0, 0b01001010, 0};
    encode_hamming7_4(c1, outBuffer1, sizeof(outBuffer1));
    REQUIRE(memcmp(outBuffer1, correctCW1, 6) == 0);

    uint8_t c2[1024] = {0};
    uint8_t outBuffer2[2048] = {0};
    uint8_t correctCW2[2048] = {0};
    encode_hamming7_4(c2, outBuffer2, 2048);
    REQUIRE(memcmp(outBuffer2, correctCW2, 2048) == 0);
}

TEST_CASE("Hamming (7,4) Decoding", "[hamming (7,4) decode]") {
    // Decode tests
    REQUIRE(decode_hamming7_4(0) == 0);
    REQUIRE(decode_hamming7_4(0b01001010) == 0b101);
    REQUIRE(decode_hamming7_4(0b11010010) == 1);

    for (int i = 0; i < 15; i++) {
        REQUIRE(decode_hamming7_4(encode_hamming7_4(i)) == i);
    }

    // abcd
    // 1101
    REQUIRE(decode_hamming7_4(0b01101010) == 0b0101); // Error in a
    REQUIRE(decode_hamming7_4(0b10101110) == 0b1101); // Error in b

    // abcd
    // 0011
    REQUIRE(decode_hamming7_4(0b11000110) == 0b0011); // Error in y
    REQUIRE(decode_hamming7_4(0b10001110) == 0b0011); // Error in b
    REQUIRE(decode_hamming7_4(0b10000010) == 0b0011); // Error in c
    REQUIRE(decode_hamming7_4(0b10000100) == 0b0011); // Error in d
}
