#ifndef HAMMING7_4
#define HAMMING7_4

#include <cstdint>

uint16_t encode_hamming7_4(uint8_t code);
uint8_t encode_hamming7_4chunk(uint8_t code);
int encode_hamming7_4(uint8_t *buffer, uint8_t *codeword, unsigned int size);

uint8_t decode_hamming7_4(uint8_t codeword);
uint8_t decode_hamming7_4chunk(uint8_t codeword);
void decode_hamming7_4(uint8_t *codeword, uint8_t *outBuffer, unsigned int size);

#endif
