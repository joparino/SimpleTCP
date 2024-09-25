#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>

#include "socket.h"

namespace jp 
{
	class ServerSocket : public Socket
	{
	public:
		ServerSocket(int port);

		/**
	 	* accept - Accepts a new incoming connection on the server socket.
		* @return: The file descriptor for the accepted socket, or -1 on error.
		*/
		int accept();

	private:
		/**
	 	* bind - Binds the server socket to the specified port to listen for incoming connections.
		* @port: The port number to bind the server socket to.
		*/
		void bind(int port);

		/**
	 	* listen - Prepares the server socket to accept incoming connections.
		* This function sets the maximum number of pending connections.
		*/
		void listen();
		
		/**
	 	* accept_with_timeout - Accepts incoming connections with a timeout to avoid blocking indefinitely.
		* @return: The file descriptor for the accepted socket, or -1 if a timeout occurs or an error occurs.
		*/
		int accept_with_timeout();

	private:
		const int m_time_await_accept{ 1 };
	};
} 
