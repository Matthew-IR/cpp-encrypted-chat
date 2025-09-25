#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "network.hpp"

Network::Network() {
    
}

bool Network::network_listen(int port) {
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

    std::cout << "Binding to port: " << port << std::endl;

    if (bind(server_socket, (struct sockaddr*)& server_address, sizeof(server_address)) < 0) {
        std::cerr << "Bind error" << std::endl;
        close(server_socket);
        return false;
    }

    if (listen(server_socket, 5) == -1) {
        std::cerr << "listen failed" << std::endl;
        close(server_socket);
        return false;
    }


    while (1) {
        int client_socket = accept(server_socket, nullptr, nullptr);
        if (client_socket == -1) {
            std::cerr << "Accept error" << std::endl;
            close(server_socket);
            return false;
        }

        close(client_socket);
        std::cout << "Connected" << std::endl;        
    }

    close(server_socket);
    return false;


};

int Network::network_connect(const std::string& ip_address, int port) {

    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        std::cerr << "socket error" << std::endl;
        return -1;
    }

    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);

    if (inet_pton(AF_INET, ip_address.c_str(), &server_address.sin_addr) <= 0) {
        std::cerr << "invalid IP address or address not supported" << std::endl;
        close(client_socket);
        return -1;
    }

    if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        std::cerr << "connection error" << std::endl;
        close(client_socket);
        return -1;
    }

    return client_socket;
};

bool Network::send_data(const std::string& data) {

};

std::string Network::receive_data() {

};

void Network::disconnect() {

};


Server::Server(int port) : PORT(port) {

};

void network_listen();

void send_data(const std::string& data);

std::string receive_data();

Server::~Server() {
    close(new_socket);
    close(server_fd);
};