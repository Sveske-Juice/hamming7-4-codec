#include "hamming7_4.h"
#include <cstdio>

uint8_t encode_hamming7_4(uint8_t code) {
    uint8_t codeword = 0;
    encode_hamming7_4(&code, &codeword, 1);
    return codeword;
}

int encode_hamming7_4(uint8_t* buffer, uint8_t* codeword, unsigned int size) {
    for (int i = 0; i < size; i++) {
        uint8_t code = buffer[i];

        code <<= 4;
        uint8_t a = code & (1 << 7);
        uint8_t b = code & (1 << 6);
        uint8_t c = code & (1 << 5);
        uint8_t d = code & (1 << 4);

        uint8_t x = (a>>4)^(b>>3)^(d>>1);
        uint8_t y = (a>>5)^(c>>3)^(d>>2);
        uint8_t z = (b>>5)^(c>>4)^(d>>3);

        printf("a:%d,b:%d,c:%d,d:%d,x:%d,y:%d,z:%d, code: %d\n", a, b, c, d, x, y, z, code | x | y | z);
        codeword[i] = code | x | y | z;
    }
    return 0;
}
