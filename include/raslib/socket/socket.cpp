#include "socket.hpp"

namespace rs
{
    SockServer::SockServer(std::string ip, int port)
    {
        this->m_ip = ip;
        this->m_port = port;
        this->m_socket = socket(AF_INET, SOCK_STREAM, 0);
        if(this->m_socket != -1)
            out("Socket created");
        else
            out("Server can't be created");

        this->m_addr_server.sin_addr.s_addr = inet_addr(this->m_ip.c_str());
        this->m_addr_server.sin_family = AF_INET;
        this->m_addr_server.sin_port = htons(this->m_port);
    }

    int SockServer::bind_sock()
    {
        if(bind(this->m_socket, (sockaddr*)&this->m_addr_server, sizeof(this->m_addr_server)) != -1)
        {
            out("Server bind on : " + this->m_ip);
            return 0;
        }
        out("Server can't bind on : " + this->m_ip);
        return -1;
    }

    int SockServer::listen_clients(int connections)
    {
        this->m_connections = connections;
        if(listen(this->m_socket, this->m_connections) != -1)
        {
            out("Server listen on port $i", this->m_port);
            return 0;
        }
        out("Server can't listen on port $i", this->m_port);
        return -1;
    }

    int SockServer::received()
    {
        int signal {0};

        out("Wait for client ...");
        struct sockaddr_in addr_client;
        socklen_t csize = sizeof(addr_client);

        int socket_cli {accept(this->m_socket, (sockaddr*)&addr_client, &csize)};
        out("Connection accepted. Client id : $i", socket_cli);
        recv(socket_cli, &signal, sizeof(signal), 0);
        close(socket_cli);
        
        return signal;
    }

    void SockServer::close_sock()
    {
        close(this->m_socket);
    }
}