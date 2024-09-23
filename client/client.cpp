#include <iostream>
#include <format>
#include "client.h"

jp::Client::Client(const std::string& client, int port, std::chrono::seconds delay):
    m_name(client),
    m_port(port), 
    m_delay(delay), 
    m_context(), 
    m_socket(m_context)
{
    connect();
}

void jp::Client::run() 
{
    std::string msg{};
    while (true) 
    {
        std::chrono::time_point<std::chrono::system_clock> time_now = std::chrono::system_clock::now();
        msg = std::format("[{0:%F} {0:%T}] {1}\n", time_now, m_name);

        boost::asio::write(m_socket, boost::asio::buffer(msg), m_error);
        if (m_error) 
        {
            std::cerr << "Send failed: " << m_error.message() << std::endl;
            break;
        }

        std::this_thread::sleep_for(m_delay);
    }
}

void jp::Client::connect() 
{
    m_socket.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), m_port), m_error);

    if (m_error)
    {
        std::cerr << "Error occurs: " << m_error.what() << std::endl;
        throw std::runtime_error("Failed to connect to the server.");
    }
}
