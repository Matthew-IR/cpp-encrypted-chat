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

    if (args[1] == "listen") {
        // connected = peer_network.network_listen(PORT);
        Server server(8080);
        server.network_listen();

    } else if (args[1] == "connect") {
        if (args.size() < 3) {
            std::cerr << "Usage: " << args[0] << " connect <ip_address>" << std::endl;
            return 1;
        }
        
        Client client("127.0.0.1", 8080);
        client.connect_to_server();

    }

    return 0;
};