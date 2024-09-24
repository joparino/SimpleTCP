#pragma once

#include <memory>
#include <vector>
#include <thread>
#include <semaphore>

#include "session.h"

namespace jp
{
	constexpr int timeAwaitAccept{ 10 };
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

		void run_forever();

	private:
		void check_sessions();
		void set_socket_timeout(int sec);
		static void handle_signal(int signal);

	private:
		int m_server{};
		std::shared_ptr<Logger> m_logger{ new Logger() };
		std::vector<std::shared_ptr<Session>> m_sessions{};
		static bool m_stop;
	};
}
