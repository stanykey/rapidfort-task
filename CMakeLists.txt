cmake_minimum_required(VERSION "3.5")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(primes)

find_package(Boost REQUIRED)
find_package(spdlog REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(core)

add_subdirectory(client)
add_subdirectory(server)
