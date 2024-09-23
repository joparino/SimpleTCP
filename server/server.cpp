#include <iostream>
#include <functional>
#include <unistd.h>
#include <cstring>
#include <csignal>
#include <sys/socket.h>
#include <netinet/in.h>

#include "server.h"

bool jp::Server::m_stop{ false };

void jp::Server::handle_signal(int signal) 
{
    m_stop = true;
}

jp::Server::Server(int port)
{
    std::signal(SIGINT, handle_signal);

    m_server = socket(AF_INET, SOCK_STREAM, 0);
    if (m_server < 0) 
    {
        throw std::runtime_error("Failed to create socket: " + std::string(strerror(errno)));
    }

    set_socket_timeout(timeSleep);

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(m_server, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) < 0) 
    {
        close(m_server);
        throw std::runtime_error("Binding failed: " + std::string(strerror(errno)));
    }

    if (listen(m_server, SOMAXCONN) < 0)
    {
        close(m_server);
        throw std::runtime_error("Listen failed: " + std::string(strerror(errno)));
    }
}


void jp::Server::run_forever()
{
    while (!m_stop)
    {
        std::cerr << "Sessions num " << m_sessions.size() << std::endl;
        if (m_sessions.size() < numThread) [[likely]]
        {
            int socket = accept(m_server, nullptr, nullptr);
            if (socket < 0)
            {
                if (errno == EAGAIN || errno == EWOULDBLOCK) 
                {
                    continue;
                }
                std::cerr << "Error on accepting socket: " << strerror(errno) << "\n";
                continue;
            }

            std::shared_ptr<Session> session{ new Session(socket, m_logger) };
            std::thread([this, session]() { session->run(); }).detach();

            m_sessions.push_back(std::move(session));
        }
        else [[unlikely]]
        {
            check_sessions();
            std::this_thread::sleep_for(timeSleepThread);
        }
    }

    std::cout << "Shutting down server...\n";
    close(m_server);
}


void jp::Server::check_sessions()
{
    std::erase_if(m_sessions, [&](const std::shared_ptr<Session>& session) {
        return !session->is_running();
    });
}


void jp::Server::set_socket_timeout(int seconds)
{
    struct timeval tv;
    tv.tv_sec = seconds;
    tv.tv_usec = 0;

    setsockopt(m_server, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
}
