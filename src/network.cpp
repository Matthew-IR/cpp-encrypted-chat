#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "network.hpp"

Server::Server(int port) : PORT(port) {

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::cerr << "Socket error" << std::endl;
        exit;
    }

    // sockaddr_in server_address;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    std::cout << "Binding to port: " << port << std::endl;

    if (bind(server_fd, (struct sockaddr*)& addr, sizeof(addr)) < 0) {
        std::cerr << "Bind error" << std::endl;
        exit;
    }
};

void Server::network_listen() {
    if (listen(server_fd, 5) < 0) {
        std::cerr << "listen failed" << std::endl;
        exit;
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&addr, (socklen_t*)&ip_len)) < 0) {
        std::cerr << "Accept error" << std::endl;
        exit;
    }

    std::cout << "Connected" << std::endl;        
    
};

void Server::send_data(const std::string& data) {
    
};

std::string Server::receive_data() {

};

Server::~Server() {
    close(new_socket);
    close(server_fd);
};


Client::Client(const std::string& server_ip, int port) : SERVER_IP(server_ip), PORT(port) {
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "socket error" << std::endl;
        exit;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, SERVER_IP.c_str(), &server_addr.sin_addr) <= 0) {
        std::cerr << "invalid IP address or address not supported" << std::endl;
        exit;
    }
};

void Client::connect_to_server() {
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "connection error" << std::endl;
        exit;
    }
};

void Client::send_data(const std::string& data) {

};

std::string Client::receive_data() {

};

Client::~Client() {
    close(sock);
};