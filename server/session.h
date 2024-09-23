#pragma once

#include <boost/asio.hpp>

#include "logger.h"

namespace jp
{
    using namespace boost::system;
    using namespace boost::asio;
    using ip::tcp;

    class Session
    {
    public:
        Session(tcp::socket socket, Logger& logger);
        
        void run();
        bool is_running() const;

    private:
        std::string read();

    private:
        bool m_running{ true };
        tcp::socket m_socket;
        Logger& m_logger;
        error_code m_error;
        streambuf m_buffer;
    };
}
