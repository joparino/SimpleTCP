#include <iostream>

#include "server.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Invalid arguments. Usage: server port" << std::endl;
        return 0;
    }

    try
    {
        jp::Server server{ std::stoi(argv[1]) };
        server.run_forever();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
