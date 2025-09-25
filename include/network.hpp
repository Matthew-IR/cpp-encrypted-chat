#pragma once
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>

class Network {
    public:
        Network();

        bool network_listen(int port);

        int network_connect(const std::string& ip_address, int port);

        bool send_data(const std::string& data);

        std::string receive_data();

        void disconnect();
    
    private:
        int client_socket;
};


class Server {
    private:
        int server_fd, new_socket;
        struct sockaddr_in addr;
        int ip_len;
        const int PORT;
    
    public:
        Server(int port);
        
        void network_listen();

        void send_data(const std::string& data);

        std::string receive_data();

        ~Server();

};


class Client {
    private:
        int sock;
        struct sockaddr_in server_addr;
        const int PORT;
        const std::string SERVER_IP;

    public:
        Client(const std::string& server_ip, int port);

        void connect_to_server();

        void send_data(const std::string& data);

        std::string receive_data();

        ~Client();
};