#include "network.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "handle_crypto.hpp"

int main(int argc, char* argv[]) {

    const int PORT = 8080;

    std::vector<std::string> args(argv, argv + argc);

    if (args.size() < 2) {
        return 1;
    } 


    if (args[1] == "listen") {
        // connected = peer_network.network_listen(PORT)
        

        DHExchange dh;
        dh.generate_parameters();

        
        Server server(8080);
        server.network_listen();
        while (true) {
            std::string clientmessage = server.receive_data();
            std::cout << "Client: " << clientmessage << std::endl;
            if (clientmessage == "exit") {
                break;
            }
            server.send_data("Success Message");
        }


    } else if (args[1] == "connect") {
        if (args.size() < 3) {
            std::cerr << "Usage: " << args[0] << " connect <ip_address>" << std::endl;
            return 1;
        }
        
        Client client("127.0.0.1", 8080);
        client.connect_to_server();
        // client.send_data("Test");

        while (true) {
            std::cout << "You: ";
            std::getline(std::cin, args[2]);
            client.send_data(args[2]);
            if (args[2] == "exit") {
                break;
            }

            std::string returnmessage = client.receive_data();
            std::cout << "Server: " << returnmessage << std::endl;

        }


    }

    return 0;
};