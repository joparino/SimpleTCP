#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include "client_socket.h"

jp::ClientSocket::ClientSocket(int port) 
{
	connect_to_server(port);
}


jp::ClientSocket::~ClientSocket() 
{
	close_socket();
}


void jp::ClientSocket::connect_to_server(int port) 
{
	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_socket < 0) 
	{
		throw std::runtime_error("Failed to create socket.");
	}

	sockaddr_in server_addr{};
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) 
	{
		close_socket();
		throw std::runtime_error("Invalid server address.");
	}

	if (connect(m_socket, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) < 0) 
	{
		close_socket();
		throw std::runtime_error("Failed to connect to the server.");
	}
}


std::size_t jp::ClientSocket::send_message(const std::string& message) 
{
	return send(m_socket, message.c_str(), message.size(), 0);
}


bool jp::ClientSocket::is_alive() const 
{
	int error = 0;
	socklen_t len = sizeof(error);
	return (getsockopt(m_socket, SOL_SOCKET, SO_ERROR, &error, &len) == 0 && error == 0);
}


void jp::ClientSocket::close_socket() 
{
	if (m_socket >= 0) 
	{
		close(m_socket);
		m_socket = -1;
	}
}
