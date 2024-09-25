#include <iostream>
#include <format>
#include <thread>
#include <csignal>

#include "client.h"
#include "utils.h"

bool jp::Client::m_running{ true };

void jp::Client::handle_signal(int signal) 
{
    m_running = false;
}


jp::Client::Client(const std::string& client, int port, std::chrono::seconds delay):
    m_name(client),
    m_port(port), 
    m_delay(delay),
    m_socket(port)
{
    std::signal(SIGINT, handle_signal);
}


void jp::Client::run() 
{
    std::string msg{};
    std::size_t sent{};
    while (m_running) 
    {
        if (!m_socket.is_alive())
        {
            break;
        }

        msg.clear();
        msg = create_message();
        sent = m_socket.send_message(msg);
        if (sent < 0) 
        {
            log_error("Send failed: ");
            break;
        }

        std::this_thread::sleep_for(m_delay);
    }
}


std::string jp::Client::create_message()
{
    std::chrono::time_point<std::chrono::system_clock> time_now = std::chrono::system_clock::now();
    return std::format("[{0:%F} {0:%T}] {1}\n", time_now, m_name);
}
