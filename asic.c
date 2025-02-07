#include "asic.h"
#include "driver-bitmain.h"
#include <string.h>
#include <stdio.h>

// Initialize the ASIC chips
ASIC_Status asic_init() {
    printf("Initializing ASICs...\n");
    if (bitmain_init() != 0) {
        return ASIC_ERROR_INIT;
    }
    return ASIC_OK;
}

// Compute SHA-256 hash using the ASIC
ASIC_Status asic_compute_hash(const uint8_t *input, uint8_t *output) {
    struct bitmain_rxnonce_data rx_nonce_data;
    int nonce_count = 0;

    struct bitmain_txtask_token task_token;
    memset(&task_token, 0, sizeof(task_token));
    task_token.token_type = BITMAIN_TOKEN_TYPE_TXTASK;
    task_token.length = sizeof(task_token);
    task_token.version = 1; // Assuming version 1
    task_token.new_block = 1; // Assuming new block
    task_token.diff = 1; // Assuming difficulty 1
    memcpy(task_token.works[0].data2, input, 12);

    int tx_result = bitmain_set_txtask((uint8_t *)&task_token, sizeof(task_token));
    if (tx_result < 0) {
        return ASIC_ERROR_COMMUNICATION;
    }

    int rx_result = bitmain_parse_rxnonce((uint8_t *)&rx_nonce_data, sizeof(rx_nonce_data), &nonce_count);
    if (rx_result < 0) {
        return ASIC_ERROR_HASH;
    }

    if (nonce_count > 0) {
        memcpy(output, &rx_nonce_data.nonces[0].nonce, 32);
        return ASIC_OK;
    }

    return ASIC_ERROR_HASH;
}

// Cleanup ASIC resources
ASIC_Status asic_cleanup() {
    printf("Cleaning up ASIC resources...\n");
    if (bitmain_cleanup() != 0) {
        return ASIC_ERROR_COMMUNICATION;
    }
    return ASIC_OK;
}
