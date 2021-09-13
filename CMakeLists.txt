cmake_minimum_required(VERSION "3.5")

project(primes)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


include_directories(core)


add_subdirectory(client)
add_subdirectory(server)
