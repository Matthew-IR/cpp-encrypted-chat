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
        // Generate parameters and public/private key pair
        dh.generate_parameters();

        
        Server server(8080);
        server.network_listen();

        // Send public parameters
        server.send_data(dh.convert_integer_to_hex(dh.get_p()));
        server.send_data(dh.convert_integer_to_hex(dh.get_g()));

        // Receive client public key
        std::string client_pub_key_str = server.receive_data();


        // Send server public key to client
        server.send_data(dh.convert_key_to_hex(dh.get_public_key()));

        std::cout << "client pub key: " << (client_pub_key_str) << std::endl;
        std::cout << "server pub key: " << dh.convert_key_to_hex(dh.get_public_key()) << std::endl;
        
        // Shared secret
        dh.generate_shared_secret(dh.convert_hex_to_key(client_pub_key_str));
        std::cout << "Shared secret: :: " << dh.convert_key_to_hex(dh.get_shared_secret()) << std::endl;

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
        
        DHExchange dh_client;

        // Receive public parameters
        std::string p_str = client.receive_data();
        std::string g_str = client.receive_data();

        // Generate client public and private key
        dh_client.set_parameters(dh_client.convert_hex_to_integer(p_str), dh_client.convert_hex_to_integer(g_str));
        dh_client.generate_keys();

        // Send client public key to server
        client.send_data(dh_client.convert_key_to_hex(dh_client.get_public_key()));

        // Receive server public key
        std::string server_pub_key_str = client.receive_data();

        std::cout << "server pub key: " << (server_pub_key_str) << std::endl;
        std::cout << "client pub key: " << dh_client.convert_key_to_hex(dh_client.get_public_key()) << std::endl;

        // Shared secret
        dh_client.generate_shared_secret(dh_client.convert_hex_to_key(server_pub_key_str));
        std::cout << "Shared secret: :: " << dh_client.convert_key_to_hex(dh_client.get_shared_secret()) << std::endl;

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