#include "hamming7_4.h"
#include <unordered_map>

std::unordered_map<uint8_t, uint8_t> codewordToDecoded = {
    {0b00000000, 0},  {0b11010010, 1},  {0b01010100, 2},  {0b10000110, 3},
    {0b10011000, 4},  {0b01001010, 5},  {0b11001100, 6},  {0b00011110, 7},
    {0b11100000, 8},  {0b00110010, 9},  {0b10110100, 10}, {0b01100110, 11},
    {0b01111000, 12}, {0b10101010, 13}, {0b00101100, 14}, {0b11111110, 15},
};

uint16_t encode_hamming7_4(uint8_t code) {
    uint8_t codeword[] = {0, 0};
    encode_hamming7_4(&code, codeword, 1);
    return (uint16_t) codeword[0] | (uint16_t) codeword[1];
}

int encode_hamming7_4(uint8_t *buffer, uint8_t *codeword, unsigned int size) {
    for (int i = 0; i < size; i++) {
        uint8_t code = buffer[i];

        // Encode lower part
        codeword[i * 2] = encode_hamming7_4chunk(code);

        // Encode upper part
        codeword[i * 2 + 1] = encode_hamming7_4chunk(code >> 4);
    }
    return 0;
}

uint8_t encode_hamming7_4chunk(uint8_t code) {
    // Go from 0 0 0 0 x3 x2 x1 x0 -> 0 0 0 x3 x2 x1 x0 0
    code <<= 1;

    // Swap x3 and p2: p0 p1 p2 x3 x2 x1 x0 -> p0 p1 x3 p2 x2 x1 x0 0
    uint8_t tmp = ((code >> 5) & 1) ^ ((code >> 4) & 1);
    tmp = (tmp << 4) | (tmp << 5);
    code ^= tmp;

    uint8_t x3 = code & (1 << 5);
    uint8_t x2 = code & (1 << 3);
    uint8_t x1 = code & (1 << 2);
    uint8_t x0 = code & (1 << 1);

    uint8_t p0 = (x3 << 2) ^ (x2 << 4) ^ (x0 << 6);
    uint8_t p1 = (x3 << 1) ^ (x1 << 4) ^ (x0 << 5);
    uint8_t p2 = (x2 << 1) ^ (x1 << 2) ^ (x0 << 3);

    return code | p0 | p1 | p2;
}

void decode_hamming7_4(uint8_t *codewordBuf, uint8_t *outBuffer,
                      unsigned int size) {
    for (int i = 0; i < size; i++) {
        uint8_t lower = decode_hamming7_4chunk(codewordBuf[i]);
        uint8_t upper = decode_hamming7_4chunk(codewordBuf[++i]) << 4;
        outBuffer[i] = lower | upper;
    }
}

uint8_t decode_hamming7_4chunk(uint8_t codeword) {
    // Check for valid codewords
    if (auto it = codewordToDecoded.find(codeword);
        it != codewordToDecoded.end()) {
        return it->second;
    } else {
        // Codeword is not valid - try and fix it
        uint8_t p0 = (codeword >> 7) & 1;
        uint8_t p1 = (codeword >> 6) & 1;
        uint8_t x3 = (codeword >> 5) & 1;
        uint8_t p2 = (codeword >> 4) & 1;
        uint8_t x2 = (codeword >> 3) & 1;
        uint8_t x1 = (codeword >> 2) & 1;
        uint8_t x0 = (codeword >> 1) & 1;

        // calculate the syndrome bits
        uint8_t p0_prime = x3 ^ x2 ^ x0;
        uint8_t p1_prime = x3 ^ x1 ^ x0;
        uint8_t p2_prime = x2 ^ x1 ^ x0;

        // error in x3
        if (p0 != p0_prime && p1 != p1_prime && p2 == p2_prime)
            codeword ^= 1 << 5;
        // error in x2
        else if (p0 != p0_prime && p1 == p1_prime && p2 != p2_prime)
            codeword ^= 1 << 3;
        // error in x1
        else if (p0 == p0_prime && p1 != p1_prime && p2 != p2_prime)
            codeword ^= 1 << 2;
        // error in x0
        else if (p0 != p0_prime && p1 != p1_prime && p2 != p2_prime)
            codeword ^= 1 << 1;

        // write data bits to output positions 0 0 0 0 x3 x2 x1 x0
        uint8_t decoded = 0;
        decoded |= ((codeword >> 5) & 1) << 3; // x3
        decoded |= ((codeword >> 3) & 1) << 2; // x2
        decoded |= ((codeword >> 2) & 1) << 1; // x1
        decoded |= ((codeword >> 1) & 1);      // x0
        return decoded;
    }
}
