# URL Shortener in C

## Overview

This program is a simple URL shortener written in C. It creates a shortened version of a given long URL and runs an HTTP server that can redirect the short URL to the original long URL.

The key components of the program are:
- **SHA-256 Hashing**: Used to generate a short code from the long URL.
- **libmicrohttpd**: A lightweight HTTP server library used to handle HTTP requests.
- **File Storage**: The URL mappings (short URL to long URL) are stored in a text file (`url_mapping.txt`).

## How It Works

1. **URL Input**: The user inputs a long URL.
2. **Short Code Generation**: The program generates a 6-character short code using the SHA-256 hash of the long URL.
3. **Mapping Storage**: The mapping between the short URL and the long URL is saved in a file (`url_mapping.txt`).
4. **HTTP Server**: The program starts an HTTP server on port 8888. When a user accesses the short URL via the server, the server looks up the corresponding long URL and redirects the browser to it.

## Prerequisites

- **Linux Operating System**: This program is designed to run on Linux.
- **GCC Compiler**: To compile the C program.
- **libmicrohttpd**: The HTTP server library.
- **OpenSSL**: Used for generating SHA-256 hashes.

## Installation

Ensure that you have the necessary libraries installed:

```bash
sudo apt-get update
sudo apt-get install libmicrohttpd-dev libssl-dev

## Execution

gcc c-shorturl.c -o url_shortener -lmicrohttpd -lssl -lcrypto
./url_shortener

