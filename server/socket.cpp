#include <cstring>

#include "socket.h"
#include "utils.h"

jp::Socket::Socket(int socket)
{
	m_socket = socket;
}


jp::Socket::Socket(Socket&& other):
    m_socket(other.m_socket) 
{
    other.m_socket = -1;
}


jp::Socket::~Socket()
{
	close_socket();
}


std::size_t jp::Socket::read(std::array<char, 1024>& buffer)
{
	return ::recv(m_socket, buffer.data(), buffer.size(), 0);
}


void jp::Socket::close_socket()
{
    if (m_socket >= 0)
    {
        ::close(m_socket);
        m_socket = -1;
    }
}


int jp::Socket::get_socket() const
{
    return m_socket;
}
