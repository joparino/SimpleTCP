#include <iostream>
#include <functional>
#include <unistd.h>
#include <csignal>
#include <cstring>

#include "server.h"
#include "utils.h"

bool jp::Server::m_running{ true };

void jp::Server::handle_signal(int signal) 
{
    m_running = false;
}


jp::Server::Server(int port):
    m_server_socket(port)
{
    std::signal(SIGINT, handle_signal);
}


jp::Server::~Server()
{
    for (const auto& session : m_sessions)
    {
        session->stop();
    }
    std::cout << "Shutting down server..." << std::endl;
    m_server_socket.close_socket();
}


void jp::Server::run_forever()
{
    while (m_running)
    {
        #ifdef DEBUG
            std::cerr << "Sessions num " << m_sessions.size() << std::endl;
        #endif
        if (m_sessions.size() < numThread) [[likely]]
        {
            Socket socket{ m_server_socket.accept() };
            if (socket.get_socket() < 0)
            {
                if (errno == EAGAIN || errno == EWOULDBLOCK || errno == 0) 
                {
                    continue;
                }
                log_error("Error on accepting socket");
                continue;
            }

            start_session_thread(std::move(socket));
        }
        else [[unlikely]]
        {
            check_sessions();
            std::this_thread::sleep_for(timeSleepThread);
        }
    }
}


void jp::Server::start_session_thread(Socket socket)
{
    std::shared_ptr<Session> session{ new Session(std::move(socket), m_logger) };
    std::thread([session]() { session->run(); }).detach();
    m_sessions.push_back(session);
}


void jp::Server::check_sessions()
{
    std::erase_if(m_sessions, [](const auto& session) {
        return !session->is_running();
    });
}
