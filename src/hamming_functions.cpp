#include "hamming_functions.h"
#include <cstdint>

int hamming_weight(uint8_t *codeword, unsigned int size) {
    unsigned int byteIdx = 0;
    int dist = 0;

    do {
        for (uint8_t val = codeword[byteIdx]; val > 0; dist++) {
            val &= (val - 1);
        }
    } while (++byteIdx < size);
    return dist;
}
int hamming_weight(uint8_t codeword) { return hamming_weight(&codeword, 1); }

int hamming_distance(uint8_t* codeword1, uint8_t* codeword2, unsigned int size) {
    unsigned int byteIdx = 0;
    int dist = 0;

    do {
        for (uint8_t val = codeword1[byteIdx] ^ codeword2[byteIdx]; val > 0; dist++) {
            val &= (val - 1);
        }
    } while (++byteIdx < size);

    return dist;
}
int hamming_distance(uint8_t codeword1, uint8_t codeword2) { return hamming_distance(&codeword1, &codeword2, 1); }
