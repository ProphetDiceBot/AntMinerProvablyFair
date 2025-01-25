#include "asic.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

// Define the target hash to compare against
const uint8_t target_hash[32] = {
    0x61, 0xe2, 0x89, 0xeb, 0x04, 0x7f, 0x73, 0x8c,
    0x2b, 0x02, 0xc4, 0x03, 0xcb, 0x2c, 0x60, 0x0c,
    0xb1, 0x15, 0x58, 0x68, 0xca, 0xbf, 0x6c, 0xb7,
    0xd3, 0xb9, 0x1f, 0xcb, 0x68, 0xa6, 0xec, 0x9c
};

// Function to generate candidates
void generate_candidate(uint64_t nonce, uint8_t *candidate) {
    memset(candidate, 0, 64); // Clear the buffer
    memcpy(candidate, &nonce, sizeof(nonce)); // Use nonce as input
}

// Function to print a hash as a hex string
void print_hash(const uint8_t *hash) {
    for (int i = 0; i < 32; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

int main() {
    printf("Starting ProphetDice S9 Custom Firmware...\n");

    if (asic_init() != ASIC_OK) {
        printf("ASIC initialization failed!\n");
        return -1;
    }

    uint8_t candidate[64] = {0};
    uint8_t output[32] = {0};

    uint64_t nonce = 0;
    time_t start_time = time(NULL);

    while (1) {
        generate_candidate(nonce, candidate);

        if (asic_compute_hash(candidate, output) != ASIC_OK) {
            printf("Hash computation failed at nonce: %llu\n", nonce);
            asic_cleanup();
            return -1;
        }

        if (memcmp(output, target_hash, 32) == 0) {
            printf("Match found! Input: %llu\n", nonce);
            printf("Output hash: ");
            print_hash(output);
            break;
        }

        nonce++;
        if (nonce % 1000000 == 0) {
            printf("Checked %llu candidates...\n", nonce);
            time_t current_time = time(NULL);
            printf("Elapsed time: %ld seconds\n", current_time - start_time);
        }
    }

    asic_cleanup();
    return 0;
}
