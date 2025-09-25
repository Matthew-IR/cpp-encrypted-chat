#pragma once
#include <string>

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