#pragma once

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>

namespace jp 
{
	class ClientSocket 
	{
	public:
		ClientSocket(int port);
		~ClientSocket();

		/**
		* send_message - Sends a message to the connected server.
		* @message: The string message to be sent.
		* @return: The number of bytes sent; returns 0 on failure.
		*/
		std::size_t send_message(const std::string& message);

		/**
		* is_alive - Checks if the socket is still connected to the server.
		* @return: True if the socket is alive, false otherwise.
		*/
		bool is_alive() const;

		/**
		* close_socket - Closes the socket connection and cleans up resources.
		*/
		void close_socket();

	private:
		/**
	 	* connect_to_server - Establishes a connection to the server at the specified port.
	 	* @port: The port number to connect to.
	 	*/
		void connect_to_server(int port);

	private:
		int m_socket{-1};
	};
} 
