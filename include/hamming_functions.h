#ifndef HAMMING_FUNCTIONS
#define HAMMING_FUNCTIONS

#include <cstdint>

int hamming_weight(uint8_t codeword);
int hamming_weight(uint8_t* codeword, unsigned int size);

int hamming_distance(uint8_t codeword1, uint8_t codeword2);
int hamming_distance(uint8_t* codeword1, uint8_t* codeword2, unsigned int size);

#endif
