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

		/**
	 	* log - Writes a log message to the log file with thread safety.
		* @msg: The message to be logged.
		*/
		void log(const std::string& msg);

	private:
		std::mutex m_mutex;
		std::ofstream m_logFile;
	};
}
