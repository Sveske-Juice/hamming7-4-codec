This is a low-level hamming (7,4,3) codec, written in C++ using bitwise operators.

This codec is part of my [SOP](https://eng.uvm.dk/upper-secondary-education/national-upper-secondary-education-programmes/the-higher-technical-examination-programme--htx-).
The project report, can be read [here](https://github.com/Sveske-Juice/hamming7-4-codec/blob/dd7fc7e6e56def173401aa85b3a24f58be36c71a/error_correction_codes_carl_benjamin_s_dreyer_sop_2023.pdf) (in danish).

# Features
- [x] Encode bytes
- [x] Encode block of bytes
- [x] Decode bytes
- [x] Decode block of bytes
- [x] Hamming Distance utility function
- [x] Hamming weight utility function
- [ ] [SEC-DEC](https://en.wikipedia.org/wiki/Hamming_code#Hamming_codes_with_additional_parity_(SECDED)) extra parity bit for double error detection

## Build
If you're on Linux just type `make` in the root directory and it will build the program and unit tests for you.

Manual:
```
mkdir -p build/
cd build/
cmake ..
```
Then to only build program:\
`make hamming`\
the unit tests:\
`make tests`\
or build all:\
`make`

## How to use
You can use this as a library if you remove main.cpp.

* **encoding:** 4 bits (4 lower bits of a `uint8_t`), gets encoded to 7 bits (7 lower bits of `uint8_t`).
* **decoding:** 7 bits (7 lower bits of a `uint8_t`), gets decoded to 4 bits (4 lower bits of `uint8_t`).

### Encoding
#### Encode single chunk
To encode a chunk (4bits) into a 7bit codeword, use the `uint8_t encode_hamming7_4chunk(uint8_t)` function.

Example:
```cpp
uint8_t code = 0b0101;
uint8_t codeword = encode_hamming7_4chunk(code); // Should be equal to 0b01001010
```

#### Encoding block of data
To encode a block of data, use the `int encode_hamming7_4(uint8_t *buffer, uint8_t *codeword, unsigned int size)` function.
* **buffer:** a pointer pointing to the data to be encoded
* **codeword:** a pointer to a buffer where the codeword should be written to. **MUST** be at least twice as big as **buffer**.
* **size:** the count of elements in **buffer** to encode.

Example:
```cpp
uint8_t* data = (uint8_t *) "Here i have some data to be encoded";

// Allocate for codeword buffer (twice as big as data buffer)

size_t data_size = strlen(data);
uint8_t* codeword = (uint8_t *) malloc(sizeof(uint8_t) * data_size * 2);

// Encode block

int rc = encode_hamming7_4(data, codeword, data_size);
```

### Decoding
#### Decode single chunk
To decode a single codeword (7 bits) to a 4bit code/chunk, use the `uint8_t decode_hamming7_4chunk(uint8_t)` function.

Example:
```cpp
uint8_t codeword = 0b01001010;
uint8_t code = decode_hamming7_4chunk(code); // Should be equal to 0b01010
```

#### Decode block of data
To decode a block of data, use the `void decode_hamming7_4(uint8_t *codewordBuf, uint8_t *outBuffer, unsigned int size)` function.
* **codewordBuf:** a pointer pointing to the data to be decoded
* **outBuffer:** a pointer to a buffer where the decoded codewords should be written to. **MUST** at least be as big as half of **codewordBuf** (**size/2**).
* **size:** the count of elements in **codewordBuf** to decode.

Example:
```cpp
// The encoded data (in this example it comes from stdin):

std::vector<uint8_t> codewordBuf(std::istreambuf_iterator<char>(std::cin), {});

// Allocate for codeword buffer (twice as big as data buffer)

size_t inputSize = codewordBuf.size();
size_t outSize = inputSize / 2;
uint8_t* decoded_data = (uint8_t *) malloc(sizeof(uint8_t) * outSize);

// Decode block

decode_hamming7_4(codewordBuf.data(), decoded_data, inputSize);
```







