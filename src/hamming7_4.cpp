#include "hamming7_4.h"
#include <bitset>
#include <iostream>
#include <unordered_map>

std::unordered_map<uint8_t, uint8_t> codewordToDecoded = {
    {0b00000000, 0},  {0b11010010, 1},  {0b01010100, 2},  {0b10000110, 3},
    {0b10011000, 4},  {0b01001010, 5},  {0b11001100, 6},  {0b00011110, 7},
    {0b11100000, 8},  {0b00110010, 9},  {0b10110100, 10}, {0b01100110, 11},
    {0b01111000, 12}, {0b10101010, 13}, {0b00101100, 14}, {0b11111110, 15},
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

// uint16_t encode_hamming7_4(uint8_t code) {
//     uint16_t codeword = 0;
//     // encode_hamming7_4(&code, &codeword, 1);
//     return codeword;
// }

int encode_hamming7_4(uint8_t *buffer, uint8_t *codeword, unsigned int size) {
    for (int i = 0; i < size; i++) {
        // FIRST 4 LSB
        uint8_t code = buffer[i];

        // Go from b8 b7 b6 b5 b4 b3 b2 b1 -> b7 b6 b5 b4 b3 b2 b1 0
        code <<= 1;

        // Swap a and z in between y and z: x y z a b c d -> x y a z b c d p4
        uint8_t tmp = ((code >> 5) & 1) ^ ((code >> 4) & 1);
        tmp = (tmp << 4) | (tmp << 5);
        code ^= tmp;

        uint8_t a = code & (1 << 5);
        uint8_t b = code & (1 << 3);
        uint8_t c = code & (1 << 2);
        uint8_t d = code & (1 << 1);

        uint8_t x = (a << 2) ^ (b << 4) ^ (d << 6);
        uint8_t y = (a << 1) ^ (c << 4) ^ (d << 5);
        uint8_t z = (b << 1) ^ (c << 2) ^ (d << 3);

        codeword[i*2] = code | x | y | z;

        // LAST 4 LSB
        code = buffer[i];

        // Go from b8 b7 b6 b5 b4 b3 b2 b1 -> 0 0 0 b8 b7 b6 b5 b4
        code >>= 3;
        // rm b4
        code &= ~0 ^ 1;

        // Swap a and z in between y and z: x y z a b c d -> x y a z b c d p4
        tmp = ((code >> 5) & 1) ^ ((code >> 4) & 1);
        tmp = (tmp << 4) | (tmp << 5);
        code ^= tmp;

        a = code & (1 << 5);
        b = code & (1 << 3);
        c = code & (1 << 2);
        d = code & (1 << 1);

        x = (a << 2) ^ (b << 4) ^ (d << 6);
        y = (a << 1) ^ (c << 4) ^ (d << 5);
        z = (b << 1) ^ (c << 2) ^ (d << 3);
        uint16_t lastpart = code | x | y | z;
        codeword[i*2+1] = lastpart;
    }
    return 0;
}

// uint8_t decode_hamming7_4(uint16_t codeword) {
//     uint8_t code = 0;
//     decode_hamming7_4(&codeword, &code, 1);
//     return code;
// }

int decode_hamming7_4(uint8_t *codewordBuf, uint8_t *outBuffer,
                      unsigned int size) {
    for (int i = 0; i < size; i++) {
        uint8_t lsb4 = decodeChunk(codewordBuf[i]);
        uint8_t msb4 = decodeChunk(codewordBuf[++i]) << 4;
        outBuffer[i] = lsb4 | msb4;
    }
    return 0;
}

uint8_t decodeChunk(uint8_t codeword) {
    // Check for valid codewords
    if (auto it = codewordToDecoded.find(codeword);
        it != codewordToDecoded.end()) {
        return it->second;
    } else {
        // Codeword is not valid - try and fix it
        uint8_t x = (codeword >> 7) & 1;
        uint8_t y = (codeword >> 6) & 1;
        uint8_t a = (codeword >> 5) & 1;
        uint8_t z = (codeword >> 4) & 1;
        uint8_t b = (codeword >> 3) & 1;
        uint8_t c = (codeword >> 2) & 1;
        uint8_t d = (codeword >> 1) & 1;

        // Calculate the syndrome bits
        uint8_t x1 = a ^ b ^ d;
        uint8_t y1 = a ^ c ^ d;
        uint8_t z1 = b ^ c ^ d;

        std::cout << "\n\nCODEWORD: " << std::bitset<8>(codeword) << std::endl;
        // Error in a
        if (x != x1 && y != y1 && z == z1) {
            codeword ^= 1 << 5;
        }

        // Error in b
        else if (x != x1 && y == y1 && z != z1) {
            codeword ^= 1 << 3;
        }

        // Error in c
        else if (x == x1 && y != y1 && z != z1) {
            codeword ^= 1 << 2;
        }

        // Error in d
        else if (x != x1 && y != y1 && z != z1) {
            codeword ^= 1 << 1;
        }

        std::cout << "CORRECTED codeword: " << std::bitset<8>(codeword)
                  << std::endl;

        // Write data bits to output positions 0b0000abcd
        uint8_t decoded = 0;
        decoded|= ((codeword >> 5) & 1) << 3; // a
        decoded|= ((codeword >> 3) & 1) << 2; // b
        decoded|= ((codeword >> 2) & 1) << 1; // c
        decoded|= ((codeword >> 1) & 1);      // d
        std::cout << "CORRECTED: " << std::bitset<8>(decoded) << std::endl;
        return decoded;
    }
}
