#if !defined(__RASLIB_SOCKET__)
#define __RASLIB_SOCKET__

    #include <raslib/raslib.hpp>

    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <unistd.h>
    #include <arpa/inet.h>

    #include <string>

    namespace rs
    {
        class SockServer
        {
            public:
                SockServer(std::string ip, int port);
                int bind_sock();
                int listen_clients(int connections);
                void received(void *object);
                void close_sock();

            private:
                std::string m_ip;

                struct sockaddr_in m_addr_server;
                int m_socket;
                int m_connections;
                int m_port;
        };
    }

#endif // __RASLIB_SOCKET__