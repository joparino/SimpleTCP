#pragma once

#include <memory>
#include <list>
#include <thread>
#include <boost/asio.hpp>

#include "session.h"

namespace jp
{
	constexpr std::chrono::seconds timeSleep{ 5 };
	#ifdef DEBUG
		const unsigned numThread{ 2 };
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

	private:
		io_context m_context{};
		tcp::acceptor m_acceptor;
		Logger m_logger{};
		std::vector<std::shared_ptr<Session>> m_sessions{};
	};
}
