project(client)

set(SOURCES main.cpp)

add_executable(client ${SOURCES})
target_link_libraries(client PRIVATE spdlog::spdlog)
