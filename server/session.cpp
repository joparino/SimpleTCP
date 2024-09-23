#include <chrono>
#include <iostream>

#include "session.h"

jp::Session::Session(ip::tcp::socket socket, Logger& logger):
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


bool jp::Session::is_running() const
{
    return m_running;
}


std::string jp::Session::read()
{
    m_buffer.consume(m_buffer.size());
    read_until(m_socket, m_buffer, "\n", m_error);
    if (m_error)
    {
        std::cerr << "Error in session: " << m_error.what() << "\n";
        m_running = false;
        return "";
    }
    return buffer_cast<const char*>(m_buffer.data());
}
