cmake_minimum_required(VERSION 3.15)

project(cpp-encrypted-chat VERSION 1.0)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Use brew's install path directly
include_directories(/opt/homebrew/opt/cryptopp/include)
link_directories(/opt/homebrew/opt/cryptopp/lib)

add_executable(cpp-encrypted-chat
    src/main.cpp
    src/handle_crypto.cpp
    src/network.cpp
)

# Add your own include/ directory
target_include_directories(cpp-encrypted-chat PUBLIC include)

# Link with Crypto++
target_link_libraries(cpp-encrypted-chat PRIVATE cryptopp)
