cmake_minimum_required(VERSION "3.5")

project(client)

find_package(Boost REQUIRED)
find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

set(HEADERS )
set(SOURCES main.cpp)

add_executable(client
    ${HEADERS}
    ${SOURCES}
)

target_link_libraries(client PRIVATE fmt::fmt-header-only)
target_link_libraries(client PRIVATE spdlog::spdlog_header_only)
