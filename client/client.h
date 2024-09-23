#pragma once

#include <boost/asio.hpp>

namespace jp
{
    using namespace boost::asio;
    using ip::tcp;

    class Client {
    public:
        Client(const std::string& clientName, int port, std::chrono::seconds delay);
        
        void run();

    private:
        void connect();
    
    private:
        std::string m_name{};
        int m_port{};
        std::chrono::seconds m_delay{};
        io_context m_context;
        tcp::socket m_socket;
        boost::system::error_code m_error{};
    };
}