#include <chrono>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>

#include "session.h"
#include "utils.h"

jp::Session::Session(Socket socket, Logger& logger):
	m_socket(std::move(socket)),
	m_logger(logger)
{}


void jp::Session::run()
{
    while (m_running)
    {
        m_logger.log(read());
    }
}


void jp::Session::stop()
{
    m_running = false;
}


bool jp::Session::is_running() const
{
    return m_running;
}


std::string jp::Session::read()
{
    std::size_t bytes_received = m_socket.read(m_buffer);
    if (bytes_received <= 0)
    {
        log_error("Error in session: ");
        stop();
        return "";
    }

    #ifdef DEBUG
        std::cerr << "Handled message:\n" << std::string(m_buffer.data(), bytes_received);
    #endif

   return std::string(m_buffer.data(), bytes_received);
}
