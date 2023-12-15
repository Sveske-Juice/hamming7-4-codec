#ifndef HAMMING7_4
#define HAMMING7_4

#include <cstdint>

uint8_t encode_hamming7_4(uint8_t code);
int encode_hamming7_4(uint8_t *buffer, uint8_t *codeword, unsigned int size);

uint8_t decode_hamming7_4(uint16_t codeword);
uint8_t decodeChunk(uint8_t codeword);
int decode_hamming7_4(uint8_t *codeword, uint8_t *outBuffer, unsigned int size);

#endif
