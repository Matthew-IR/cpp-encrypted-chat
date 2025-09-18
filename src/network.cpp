#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <network.hpp>

bool Network::listen(int port) {
    // Create socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cerr << "Socket error" << std::endl;
        return false;
    }

    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr*)& server_address, sizeof(server_address)) < 0) {
        std::cerr << "Bind error" << std::endl;
        close(server_socket);
        return false;
    }

    
};

bool Network::connect(const std::string& ip_address, int port) {

};

bool Network::send_data(const std::string& data) {

};

std::string Network::receive_data() {

};

void Network::disconnect() {

};