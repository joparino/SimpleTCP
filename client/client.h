#pragma once

#include <string>
#include <chrono>
#include <memory>

#include "client_socket.h"

namespace jp
{
    class Client {
    public:
        Client(const std::string& client_name, int port, std::chrono::seconds delay);
        
        /**
        * run - Starts the client operation, allowing it to send messages to the server
        * and handle incoming responses.
        */
        void run();

    private:
        /**
        * create_message - Creates a message to be sent to the server.
        * @return: A string containing the message to be sent.
        */
        std::string create_message();

        /**
        * handle_signal - Signal handler to gracefully shut down the client when
        * a termination signal is received (e.g., SIGINT).
        * @signal: The signal number that was received.
        */
        static void handle_signal(int signal);

    private:
        std::string m_name{};
        int m_port{};
        std::chrono::seconds m_delay{};
        ClientSocket m_socket;
        static bool m_running;
    };
}
