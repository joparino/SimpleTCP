#include <iostream>
#include <format>
#include <thread>
#include <csignal>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>

#include "client.h"

bool jp::Client::m_running{ true };

void jp::Client::handle_signal(int signal) 
{
    m_running = false;
}

jp::Client::Client(const std::string& client, int port, std::chrono::seconds delay):
    m_name(client),
    m_port(port), 
    m_delay(delay)
{
    connect_to_server();
    std::signal(SIGINT, handle_signal);
}

void jp::Client::run() 
{
    std::string msg{};
    std::size_t sent{};
    while (m_running) 
    {
        std::chrono::time_point<std::chrono::system_clock> time_now = std::chrono::system_clock::now();
        msg = std::format("[{0:%F} {0:%T}] {1}\n", time_now, m_name);

        sent = send(m_socket, msg.c_str(), msg.size(), 0);
        msg.clear();
        if (sent < 0) 
        {
            std::cerr << "Send failed: " << strerror(errno) << "\n";
            break;
        }

        std::this_thread::sleep_for(m_delay);
    }
    close(m_socket);
    std::cout << "Client stopped.\n";
}

void jp::Client::connect_to_server() 
{
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket < 0)
    {
        std::cerr << "Error creating socket: " << strerror(errno) << "\n";
        throw std::runtime_error("Failed to create socket.");
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(m_port);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    if (connect(m_socket, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) < 0)
    {
        std::cerr << "Error connecting to server: " << strerror(errno) << "\n";
        throw std::runtime_error("Failed to connect to the server.");
    }
}
