#pragma once

#include <mutex>
#include <fstream>

namespace jp
{
	class Logger
	{
	public:
		Logger();
		~Logger();

		void log(const std::string& msg);

	private:
		std::mutex m_mutex;
		std::ofstream m_logFile;
	};
}
