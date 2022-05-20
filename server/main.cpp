#include "server.hpp"

#include <spdlog/spdlog.h>


//
// application entry point
//
int main(int argc, const char* argv[])
{
    try
    {
        if (argc != 2)
        {
            spdlog::error("Usage: server <port>");
            return 1;
        }

        boost::asio::io_context io_context;
        primes::server server(io_context, std::atoi(argv[1]));
        io_context.run();
    }
    catch (const std::exception& ex)
    {
        spdlog::error("Exception: {}", ex.what());
    }

    return 0;
}
