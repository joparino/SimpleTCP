#include "utils.h"

#include <iostream>
#include <cstring>

void jp::log_error(const std::string& message)
{
		std::cerr << message << ": " << std::strerror(errno) << "\n";
}
