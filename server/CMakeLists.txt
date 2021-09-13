cmake_minimum_required(VERSION "3.5")

project(server)

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

set(HEADERS server.hpp session.hpp)
set(SOURCES main.cpp)

add_executable(server
    ${HEADERS}
    ${SOURCES}
)
