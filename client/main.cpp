#include <iostream>
#include <string>
#include <chrono>
#include <stdexcept>
#include "client.h"

int main(int argc, char* argv[]) 
{
    if (argc != 4) 
    {
        std::cerr << "Invalid arguments. Usage: client client_name port delay" << std::endl;
        return 1;
    }

    try 
    {
        jp::Client client(argv[1], std::stoi(argv[2]), std::chrono::seconds(std::stoll(argv[3])));
        client.run();
    }
    catch (const std::exception& e) 
    {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
