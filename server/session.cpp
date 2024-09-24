#include <chrono>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>

#include "session.h"

jp::Session::Session(int socket, std::shared_ptr<Logger> logger):
	m_socket(socket),
	m_logger(logger)
{}


void jp::Session::run()
{
    while (m_running)
    {
        m_logger->log(read());
    }
}


bool jp::Session::is_running() const
{
    return m_running;
}


std::string jp::Session::read()
{
    std::size_t bytes_read = recv(m_socket, m_buffer.data(), m_buffer.size(), 0);
    if (bytes_read <= 0)
    {
        std::cerr << "Error in session: " << (bytes_read < 0 ? strerror(errno) : "Connection closed") << "\n";
        m_running = false;
        return "";
    }
    #ifdef DEBUG
        std::cerr << "Handled message:\n" << std::string(m_buffer.data(), bytes_read);
    #endif
    return std::string(m_buffer.data(), bytes_read);
}
