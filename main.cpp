#include <cstdint>
#include <stdio.h>

#include "hamming_functions.h"

#define CHUNK_SIZE 7 // Amount of information bits in a codeword

const char* msg = "Hello";

int main(int argc, char** argv) {
    uint8_t cw1 = 0b00111;
    uint8_t cw2 = 0b00111;

    printf("D(%d, %d) = %d\n", cw1, cw2, hamming_distance(&cw1, &cw2, 1));

    return 0;
}
