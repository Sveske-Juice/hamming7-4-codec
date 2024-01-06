#include <cstring>
#include <iostream>
#include <iterator>
#include <unistd.h>
#include <vector>

#include "hamming7_4.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Not enough arguments provided" << std::endl;
        return 1;
    }
    else if (argc == 2 && strcmp(argv[1], "-e") == 0) {
        std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(std::cin), {});
        size_t size = buffer.size();
        // printf("input size: %zu\n", size);

        uint8_t* codewordBuffer = (uint8_t*) malloc(sizeof(uint8_t)*size*2);
        encode_hamming7_4(buffer.data(), codewordBuffer, sizeof(uint8_t)*size);

        write(STDOUT_FILENO, codewordBuffer, size*2);
    }
    else if (argc == 2 && strcmp(argv[1], "-d") == 0) {
        std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(std::cin), {});
        size_t size = buffer.size();
        size_t outSize = size / 2;

        uint8_t* decodedBuffer = (uint8_t*) malloc(sizeof(uint8_t)*outSize);
        decode_hamming7_4(buffer.data(), decodedBuffer, sizeof(uint8_t)*size);

        write(STDOUT_FILENO, decodedBuffer, outSize);
    }
    else {
        std::cerr << "Syntax error" << std::endl;
        return 2;
    }

    return 0;
}
