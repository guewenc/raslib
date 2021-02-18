#include "socket.hpp"

namespace rs
{
    SockServer::SockServer(std::string ip, int port)
    {
        this->m_ip = ip;
        this->m_port = port;
        this->m_socket = socket(AF_INET, SOCK_STREAM, 0);

        this->m_addr_server.sin_addr.s_addr = inet_addr(this->m_ip.c_str());
        this->m_addr_server.sin_family = AF_INET;
        this->m_addr_server.sin_port = htons(this->m_port);
    }

    void SockServer::bind_sock()
    {
        bind(this->m_socket, (sockaddr*)&this->m_addr_server, sizeof(this->m_addr_server));
        out("Server bind on : " + this->m_ip);
    }

    void SockServer::listen_clients(int connections)
    {
        this->m_connections = connections;
        listen(this->m_socket, this->m_connections);
        out("Server listen on port " + std::to_string(this->m_port));
    }

    void SockServer::received(void *object)
    {
        for(int i {0}; i < m_connections; i++)
        {
            struct sockaddr_in addr_client;
            socklen_t csize = sizeof(addr_client);

            int socket_cli {accept(this->m_socket, (sockaddr*)&addr_client, &csize)};
            out("Connection accepted. Client : $i", socket_cli);
            recv(socket_cli, &object, sizeof(object), 0);
        }
    }
}