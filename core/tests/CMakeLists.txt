cmake_minimum_required(VERSION "3.5")

project(core_tests)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


find_package(Catch2 CONFIG REQUIRED)


set(SOURCES runner.cpp)


add_executable(core_test_runner ${SOURCES})

target_compile_definitions(core_test_runner PRIVATE CATCH_CONFIG_RUNNER)
target_link_libraries(core_test_runner PRIVATE Catch2::Catch2)
