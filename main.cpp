#include <bitset>
#include <cstdint>
#include <iostream>

#include "hamming7_4.h"

const char* msg = "Hello";

int main(int argc, char** argv) {
    for (int i = 0; i < 16; i++) {
        uint8_t cw = encode_hamming7_4(i);
        std::cout << std::bitset<8>(cw) << std::endl;
    }

    return 0;
}
