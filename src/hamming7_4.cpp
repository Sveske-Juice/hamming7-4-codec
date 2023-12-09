#include "hamming7_4.h"
#include <bitset>
#include <cstdio>
#include <iostream>
#include <ostream>
#include <unordered_map>

std::unordered_map<uint8_t, uint8_t> codewordToDecoded = {
    {0b00000000, 0},
    {0b11010010, 1},
    {0b01010100, 2},
    {0b10000110, 3},
    {0b10011000, 4},
    {0b01001010, 5},
    {0b11001100, 6},
    {0b00011110, 7},
    {0b11100000, 8},
    {0b00110010, 9},
    {0b10110100, 10},
    {0b01100110, 11},
    {0b01111000, 12},
    {0b10101010, 13},
    {0b00101100, 14},
    {0b11111110, 15},
};

// All the syndromes packed in a parity-check matrix
uint8_t parityCheckMatrix[7][3] = {
    {1, 0, 0}, // Error in x
    {0, 1, 0}, // Error in y
    {0, 0, 1}, // Error in z
    {1, 1, 0}, // Error in a
    {1, 0, 1}, // Error in b
    {0, 1, 1}, // Error in c
    {1, 1, 1}, // Error in d
};

uint8_t encode_hamming7_4(uint8_t code) {
    uint8_t codeword = 0;
    encode_hamming7_4(&code, &codeword, 1);
    return codeword;
}

int encode_hamming7_4(uint8_t* buffer, uint8_t* codeword, unsigned int size) {
    for (int i = 0; i < size; i++) {
        uint8_t code = buffer[i];

        // Go from 0 x y z a b c d -> x y z a b c d 0
        code <<= 1;

        // Swap a and z in between y and z: x y z a b c d -> x y a z b c d p4
        uint8_t tmp = ((code >> 5) & 1) ^ ((code >> 4) & 1);
        tmp = (tmp << 4) | (tmp << 5);
        code ^= tmp;

        uint8_t a = code & (1 << 5);
        uint8_t b = code & (1 << 3);
        uint8_t c = code & (1 << 2);
        uint8_t d = code & (1 << 1);

        uint8_t x = (a<<2)^(b<<4)^(d<<6);
        uint8_t y = (a<<1)^(c<<4)^(d<<5);
        uint8_t z = (b<<1)^(c<<2)^(d<<3);

        codeword[i] = code | x | y | z;
        // std::cout << "Generated codeword from: " << std::bitset<8>(buffer[i]) << " = " << std::bitset<8>(codeword[i]) << std::endl;
    }
    return 0;
}


uint8_t decode_hamming7_4(uint8_t codeword) {
    uint8_t code = 0;
    decode_hamming7_4(&codeword, &code, 1);
    return code;
}

int decode_hamming7_4(uint8_t* codewordBuf, uint8_t* outBuffer, unsigned int size) {
    for (int i = 0; i < size; i++) {
        uint8_t codeword = codewordBuf[i];
        // Check for valid codewords
        if (auto it = codewordToDecoded.find(codeword); it != codewordToDecoded.end()) {
            outBuffer[i] = it->second;
        }
        else {
            // Codeword is not valid - try and fix it
        }
    }
    return 0;
}
