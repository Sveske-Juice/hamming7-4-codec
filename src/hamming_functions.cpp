#include "hamming_functions.h"

int hamming_distance(uint8_t* codeword1, uint8_t* codeword2, unsigned int size) {
    unsigned int byteIdx = 0;
    int dist = 0;

    do {
        for (unsigned int val = codeword1[byteIdx] ^ codeword2[byteIdx]; val > 0; dist++) {
            val &= (val - 1);
        }
    } while (++byteIdx < size);

    return dist;
}
