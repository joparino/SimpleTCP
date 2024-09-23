#pragma once

#include <chrono>

namespace jp
{
    class Client {
    public:
        Client(const std::string& clientName, int port, std::chrono::seconds delay);
        
        void run();

    private:
        void connect_to_server();
        static void handle_signal(int signal);

    private:
        std::string m_name{};
        int m_port{};
        std::chrono::seconds m_delay{};
        int m_socket;
        static bool m_running;
    };
}
