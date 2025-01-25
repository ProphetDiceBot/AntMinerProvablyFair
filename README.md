
# Antminer S9 Custom Firmware for Server Seed Cracking

This project transforms the Antminer S9 into a SHA-256 brute-forcing machine capable of computing server seed hashes efficiently.

## Features

- **ASIC Utilization**: High-performance SHA-256 hashing using BM1387 chips.
- **Parallelism**: Leverages all chains for maximum throughput.
- **Flexible**: Easily modify candidate generation logic.

## Installation

1. Install the ARM cross-compiler:
   ```bash
   sudo apt-get install gcc-arm-linux-gnueabihf
   ```

2. Compile the firmware:
   ```bash
   make
   ```

3. Flash the Antminer:
   - Format a microSD card as FAT32.
   - Copy `firmware` to the root directory of the microSD card.
   - Insert the card and boot the Antminer in recovery mode.

## Usage

Start the Antminer and monitor the output via the serial console.

## Disclaimer

For educational purposes only. Unauthorized use is prohibited.
