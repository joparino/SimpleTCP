#pragma once

#include <sys/socket.h>
#include <unistd.h>
#include <stdexcept>
#include <string>
#include <array>

namespace jp
{
    class Socket
    {
    public:
        Socket(int domain, int type, int protocol);
        Socket(int socket);
        Socket(Socket&& other);
        virtual ~Socket();

        // Copying is disabled to prevent issues with socket descriptors
        Socket(const Socket&) = delete;
        Socket& operator=(const Socket&) = delete;

        /**
        * read - Receives data from the socket into the provided buffer.
        * @buffer: The buffer where received data will be stored.
        * @return: A count of received bytes.
        */
        virtual std::size_t read(std::array<char, 1024>& buffer);

        /**
        * close_socket - Closes the socket if it is open, ensuring the descriptor is
        * invalidated after closing.
        */
        virtual void close_socket();

        /**
        * get_socket - Returns the underlying socket file descriptor.
        * @return: The integer file descriptor for the socket.
        */
        int get_socket() const;

    protected:
        int m_socket{-1};
    };
}
