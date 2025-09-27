#pragma once
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>


class Server {
    private:
        int server_fd, new_socket; ///< File descriptor for the server and client sockets.
        struct sockaddr_in addr; ///< Address structure for the server.
        int ip_len;
        const int PORT; ///< The port number the server is listening on.
    
    public:
        /** 
         * @brief Constructs a new Server object.
         * @param port The port number on which the server listens
        */
        Server(int port);
        
        /** 
         * @brief Listens for incoming network connections.
        */
        void network_listen();

        /** 
         * @brief Sends data to the connected client.
         * @param data The string of data that is being sent over the socket.
        */
        void send_data(const std::string& data);

        /** 
         * @brief Receives data from the connected client.
         * @return The data that has received as a string.
        */
        std::string receive_data();

        /** 
         * @brief Desstructor for the Server class.
        */
        ~Server();

};


class Client {
    private:
        int sock;
        struct sockaddr_in server_addr;
        const int PORT;
        const std::string SERVER_IP;

    public:
        /** 
         * @brief Constructs a new Client object.
         * @param server_ip The ip of the server that the client is connecting to
         * @param port The ip that is open on the server listening
        */
        Client(const std::string& server_ip, int port);
        /** 
         * @brief Connect to the listening server
        */
        void connect_to_server();
        /** 
         * @brief Sends data to the connected server.
         * @param data The string of data that is being sent over the socket.
        */
        void send_data(const std::string& data);
        /** 
         * @brief Receives data from the connected server.
         * @return The data that has received as a string.
        */
        std::string receive_data();
        /** 
         * @brief Desstructor for the Client class.
        */
        ~Client();
};