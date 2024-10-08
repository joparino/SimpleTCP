#include <iostream>

#include "logger.h"

jp::Logger::Logger()
{
	m_logFile.open("log.txt", std::ios::binary);
	if (!m_logFile.is_open())
	{
		std::cerr << "Cannot open file\n";
	}
}


jp::Logger::~Logger()
{
	m_logFile.close();
}


void jp::Logger::log(const std::string& msg)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	m_logFile << msg;
}
