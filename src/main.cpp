#include "network.hpp"
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {

    const int PORT = 8080;

    std::vector<std::string> args(argv, argv + argc);

    if (args.size() < 2) {
        return 1;
    } 

    Network peer_network;
    bool connected = false;
    bool connect_success = false;

    if (args[1] == "listen") {
        connected = peer_network.network_listen(PORT);

    } else if (args[2] == "connect") {
        connect_success = peer_network.connect("", PORT);
    }

    return 0;
};