# cpp-encrypted-chat

A command-line utility that communicates securly between a client and a server. This utility performs Diffie-Hellman (DH) key exchange to create a shared secret then uses that secret to create session key which is used to encrypt the messages in that conversation with AES (GCM). 

The project uses the Crypto++ library.

The project was developed as an exercise to implement cryptographic concepts. It is **not intended for real-world use**.

The focus was not on creating a production ready application. It has not been tested and may contain security vulnerabilities, e.g. input sanitisation.

**Do not use this to transmit any sensitive or private information.**

## Dependencies

- CMake 3.15
- C++ Compiler (C++23)
- Crypto++ 8.9.0
## Building
To build this project you can use CMake.

1. Clone the repository:
    ```bash
    git clone <repo-url>
    cd cpp-encrypted-chat
    ```

2. Create a build directory:
    ```bash
    mkdir build
    cd build
    ```

3. Run Cmake, and then build:
    ```bash
    cmake ..
    make
    ```

    *Note: 'CMakeLists.txt' currently contains a path to the Crypto++ library when installed with Homebrew on Apple Silison. If your path is different, you may need to change the `CMakeLists.txt` file.*

## Usage

This program has two modes: `listen` and `connect` which behave as server and client respectively.

### Server Mode

To start the server and listen for connections:
```bash
./build/cpp-encrypted-chat listen
```

Once a connection is established by a client, it will perform DH key exchange and then await messages.

### Client Mode

To connect to a server:

```bash
./build/cpp-encrypted-chat connect <server_ip_address>
```

Once connected, you can input messages into the command line. 
To close the connection type `exit` in the client.


