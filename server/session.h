#pragma once

#include <memory>

#include "socket.h"
#include "logger.h"

namespace jp
{
    class Session
    {
    public:
        Session(Socket socket, Logger& logger);
        
        /**
        * run - Runs the session, processing incoming data and logging as necessary.
        * This function blocks and continues until the session or server is stopped.
        */
        void run();

        /**
        * stop - Stops the session by setting the running flag to false.
        * This function can be called to safely terminate the session.
        */
        void stop();

        /**
        * is_running - Checks if the session is running.
        * @return: Returns true if the session is active, false otherwise.
        */
        bool is_running() const;

    private:
        /**
        * read - Reads data from the socket into a buffer and returns it as a string.
        * @return: Returns the data read from the socket. If an error occurs or no data is received, an stop called.
        */
        std::string read();

    private:
        bool m_running{ true };
        Socket m_socket;
        Logger& m_logger;
        std::array<char, 1024> m_buffer{};
    };
}
