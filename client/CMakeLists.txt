cmake_minimum_required (VERSION 3.8)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_DEBUG_LIBS OFF)
set(Boost_USE_RELEASE_LIBS ON)
set(Boost_USE_MULTITHREADED ON)


find_package(Boost REQUIRED COMPONENTS system)

add_compile_definitions(
    BOOST_ALL_NO_LIB
)

project (client)

add_executable (client "main.cpp" "client.cpp" "client.h")

target_include_directories(client PUBLIC
    ${Boost_INCLUDE_DIRS}
)

target_link_libraries(client PUBLIC
    ${Boost_LIBRARIES}
)
