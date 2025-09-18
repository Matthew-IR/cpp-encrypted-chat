#pragma once
#include <string>

class Network {
    public:
        Network();

        bool listen(int port);

        bool connect(const std::string& ip_address, int port);

        bool send_data(const std::string& data);

        std::string receive_data();

        void disconnect();
};