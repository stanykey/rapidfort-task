#include <iostream>

#include "server.hpp"


//
// application entry point
//
int main(int argc, const char* argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: server <port>\n";
            return 1;
        }

        boost::asio::io_context io_context;
        primes::server server(io_context, std::atoi(argv[1]));
        io_context.run();
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Exception: " << ex.what() << "\n";
    }

    return 0;
}
