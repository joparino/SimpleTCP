#include <iostream>

#include "server.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Invalid arguments. Usage: server port" << std::endl;
        return 0;
    }

    const int port{ std::stoi(argv[1]) };

    jp::Server server{ port };
    server.run_forever();

    return 0;
}
