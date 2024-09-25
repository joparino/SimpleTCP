#pragma once

#include <memory>
#include <list>
#include <thread>

#include "session.h"
#include "server_socket.h"

namespace jp
{
	constexpr std::chrono::seconds timeSleepThread{ 5 };
	#ifdef DEBUG
		constexpr unsigned numThread{ 2 };
	#else
		const unsigned numThread{ std::thread::hardware_concurrency() };
	#endif

	class Server
	{
	public:
		Server(int port);
		~Server();

		/**
	 	* run_forever - Enters a loop that continuously accepts and manages client sessions 
		* until the server is signaled to stop.
		*/
		void run_forever();

	private:
		/**
	 	* start_session_thread - Starts a new thread to handle a client session.
		* @socket: Socket for the newly accepted client connection.
		*/
		void start_session_thread(Socket socket);

		/**
	 	* check_sessions - Checks and removes inactive sessions from the session list.
		*/
		void check_sessions();

		/**
	 	* handle_signal - Static signal handler that stops the server when a signal is received.
		* @signal: The signal received (e.g., SIGINT).
		*/
		static void handle_signal(int signal);

	private:
		ServerSocket m_server_socket;
		Logger m_logger{};
		std::list<std::shared_ptr<Session>> m_sessions{};
		static bool m_running;
	};
}
