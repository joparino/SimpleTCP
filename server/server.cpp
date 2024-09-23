#include <iostream>

#include "server.h"

jp::Server::Server(int port):
    m_acceptor(m_context, tcp::endpoint(tcp::v4(), port))
{
    m_sessions.reserve(numThread);
}


void jp::Server::run_forever()
{
    boost::system::error_code error{};
    while (true)
    {
        std::cerr << "Sessions num " << m_sessions.size() << std::endl;
        if (m_sessions.size() < numThread) [[likely]]
        {
            tcp::socket sock{ m_context };
            m_acceptor.accept(sock, error);
            if (error)
            {
                std::cerr << "Error on acception socket" << error.what() << std::endl;
                error.clear();
                continue;
            }

            std::shared_ptr<Session> session{ new Session(std::move(sock), m_logger) };
            //std::thread(std::bind(&Session::run, session.get())).detach();
            std::thread([session](){ session->run(); }).detach();

            m_sessions.push_back(std::move(session));
        }
        else [[unlikely]]
        {
            check_sessions();
            std::this_thread::sleep_for(timeSleep);
        }
    }
}


void jp::Server::check_sessions()
{
    std::erase_if(m_sessions, [&](const std::shared_ptr<Session>& session) {
        return !session->is_running();
    });
}
