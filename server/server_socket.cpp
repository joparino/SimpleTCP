#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

#include "server_socket.h"

jp::ServerSocket::ServerSocket(int port):
    Socket(AF_INET, SOCK_STREAM, 0)
{
    bind(port);
    listen();
}


void jp::ServerSocket::bind(int port)
{
    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (::bind(m_socket, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) < 0)
    {
        close(m_socket);
        throw std::runtime_error("Binding failed");
    }
}


void jp::ServerSocket::listen()
{
    if (::listen(m_socket, SOMAXCONN) < 0)
    {
        close(m_socket);
        throw std::runtime_error("Listen failed");
    }
}


int jp::ServerSocket::accept()
{
    return accept_with_timeout();
}


int jp::ServerSocket::accept_with_timeout()
{
    fd_set read_fds;
    FD_ZERO(&read_fds);
    FD_SET(m_socket, &read_fds);

    struct timeval timeout;
    timeout.tv_sec = m_time_await_accept;
    timeout.tv_usec = 0;

    // Wait for activity on the socket with the specified timeout
    int activity = select(m_socket + 1, &read_fds, nullptr, nullptr, &timeout);
    
    if (activity < 0)
    {
        throw std::runtime_error("Select error");
    }
    else if (activity == 0)
    {
        return -1; // Return -1 for a timeout scenario
    }

    return ::accept(m_socket, nullptr, nullptr);
}
