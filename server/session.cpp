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
    char buffer[1024];
    std::size_t bytesRead = recv(m_socket, buffer, sizeof(buffer) - 1, 0);
    if (bytesRead <= 0)
    {
        std::cerr << "Error in session: " << (bytesRead < 0 ? strerror(errno) : "Connection closed") << "\n";
        m_running = false;
        return "";
    }
    buffer[bytesRead] = '\0';
    return std::string(buffer);
}
