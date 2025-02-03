# AES Encrypt/Decrypt Tool

A simple command-line tool for encrypting and decrypting files using AES (CBC mode) with the Crypto++ library. 

## Features

- **Encryption:** Encrypt a plaintext file to produce a binary encrypted file (`encrypted.bin`).
- **Decryption:** Decrypt a binary encrypted file back to plaintext (`decrypted.txt`).
- **Command-line Interface:** Easily switch between encryption and decryption modes via command-line arguments.
- **Uses Crypto++:** Leverages the Crypto++ library for cryptographic operations.

## Requirements

- **C++ Compiler:** A compiler with C++11 (or later) support (e.g., `g++`, `clang++`).
- **Crypto++ Library:**  
  - On Ubuntu/Debian-based systems, install with:
    ```bash
    sudo apt-get install libcrypto++-dev
    ```
  - On Arch install with:
    ```bash
    sudo pacman -S libcrypto++-dev
    ```
  - For other systems or detailed installation instructions, see the [Crypto++ repository](https://github.com/weidai11/cryptopp).

## Compilation

To compile the project, open a terminal in the project directory and run:

```bash
g++  -O2 main.cpp -o easyencrypt -lcryptopp
```

## Usage
Open a terminal in the project directory
```bash
./easyencrypt <decrypt/encrypt> <inputfile> <key>
```
