cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_DEBUG_LIBS OFF)
set(Boost_USE_RELEASE_LIBS ON)
set(Boost_USE_MULTITHREADED ON)

find_package(Boost REQUIRED COMPONENTS system)

add_compile_definitions(
    BOOST_ALL_NO_LIB
)

project (server)

add_executable (server "main.cpp" "server.h" "server.cpp" "session.h" "session.cpp" "logger.h" "logger.cpp")

target_include_directories(server PUBLIC
    ${Boost_INCLUDE_DIRS}
)

target_link_libraries(server PUBLIC
    ${Boost_LIBRARIES}
)
