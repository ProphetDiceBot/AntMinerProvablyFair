
#ifndef ASIC_H
#define ASIC_H

#include <stdint.h>
#include <stdbool.h>

// Error codes for ASIC functions
typedef enum {
    ASIC_OK,
    ASIC_ERROR_INIT,
    ASIC_ERROR_HASH,
    ASIC_ERROR_COMMUNICATION,
    ASIC_ERROR_POWER,
} ASIC_Status;

// Initialize the ASIC chips
ASIC_Status asic_init();

// Compute SHA-256 hash using the ASIC (takes input and puts output)
ASIC_Status asic_compute_hash(const uint8_t *input, uint8_t *output);

// Cleanup ASIC resources
ASIC_Status asic_cleanup();

#endif // ASIC_H
