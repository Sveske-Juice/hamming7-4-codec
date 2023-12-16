#include <bitset>
#include <cstring>
#include <iostream>
#include <unistd.h>

#include "hamming7_4.h"

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Not enough arguments provided" << std::endl;
        return 1;
    }
    else if (argc == 3 && strcmp(argv[1], "-e") == 0) {
        size_t size = strlen(argv[2]);

        uint8_t* codewordBuffer = (uint8_t*) malloc(sizeof(uint8_t)*size*2);
        encode_hamming7_4((uint8_t*) argv[2], codewordBuffer, sizeof(uint8_t)*size*2);

        write(STDOUT_FILENO, codewordBuffer, size*2);
        for (int i = 0; i < size*2; i++) {
            // std::cout << std::bitset<8>(*(codewordBuffer+i)) << " ";
        }
        // std::cout << std::endl;
    }
    else if (argc == 3 && strcmp(argv[1], "-d") == 0) {
        size_t size = strlen(argv[2]);

        uint8_t* decodedBuffer = (uint8_t*) malloc(sizeof(uint8_t)*size);
        decode_hamming7_4((uint8_t*) argv[2], decodedBuffer, sizeof(uint8_t)*size);

        write(STDOUT_FILENO, decodedBuffer, size);
    }
    else {
        std::cerr << "Syntax error" << std::endl;
        return 2;
    }

    return 0;
}
