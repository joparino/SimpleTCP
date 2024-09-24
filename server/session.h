#pragma once

#include "logger.h"

namespace jp
{
    class Session
    {
    public:
        Session(int socket, std::shared_ptr<Logger> logger);
        
        void run();
        bool is_running() const;

    private:
        std::string read();

    private:
        bool m_running{ true };
        int m_socket;
        std::shared_ptr<Logger> m_logger;
        std::array<char, 1024> m_buffer{};
    };
}
