project(server)

set(HEADERS server.hpp session.hpp)
set(SOURCES main.cpp)

add_executable(server ${HEADERS} ${SOURCES})
target_link_libraries(server PRIVATE spdlog::spdlog)
