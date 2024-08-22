# ASCII Communication Protocol Library

A lightweight C library for creating and parsing serial communication commands using an ASCII-based protocol. This library is designed for embedded systems and other applications where efficient and reliable serial communication is required.

## Features

**Simple and Flexible Protocol:** The library uses a custom ASCII-based protocol to encapsulate commands, payloads, and checksums.

**Command Creation and Parsing:** Functions to create and parse command strings, ensuring integrity through checksums.

**Extensible Command Set:** Easily add new commands to the protocol by updating the command_t enum and associated functions.

**Checksum Verification:** Built-in checksum calculation and verification to ensure data integrity.

**Portable:** The library is platform-agnostic, making it suitable for embedded systems, desktop applications, and more.

# Getting Started
## Prerequisites
You will need a C compiler such as GCC installed on your system. The following example assumes you are working in a UNIX-like environment.

## Building the Library
**1. Clone the Repository:**

`git clone https://github.com/esadigov/ascii-communication-protocol`

**2. Build the library:**

`make`

## Example usage

`make run_example`

## Running unit tests

`make test`