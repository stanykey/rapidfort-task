#include <iostream>
#include <string>
#include <deque>
#include <algorithm>
#include <utility>
#include <numeric>

#include <boost/asio.hpp>

#include <spdlog/spdlog.h>

#include <utils/io.hpp>
#include <utils/packed.hpp>


//
// application entry point
//
int main(int argc, const char* argv[])
{
    try
    {
        if (argc != 3)
        {
            spdlog::error("Usage: client <host> <port>");
            return 1;
        }

        boost::asio::io_context io_context;

        boost::asio::ip::tcp::socket server(io_context);
        boost::asio::ip::tcp::resolver resolver(io_context);
        boost::asio::connect(server, resolver.resolve(argv[1], argv[2]));

        std::cout << "How many primes do you want?: ";
        auto const primes_count = utils::read<std::uint64_t>(std::cin);
        spdlog::info("Client will request {} prime numbers", primes_count);

        const auto request = utils::make_packed(primes_count);
        boost::asio::write(server, boost::asio::buffer(request.data(), request.size()));

        std::deque<std::string> primes;
        for (auto i = 0u; i < request.value(); i++)
        {
            auto prime = utils::make_packed<std::uint64_t>(0);
            boost::asio::read(server, boost::asio::buffer(prime.data(), prime.size()));

            auto number = std::to_string(prime.value());
            const auto it = std::lower_bound(primes.begin(), primes.end(), number);
            const bool should_print_top_five = std::distance(primes.begin(), it) < 5;
            primes.insert(it, std::move(number));

            if (should_print_top_five)
            {
                const auto first = primes.begin();
                const auto count = std::min<std::size_t>(5, primes.size());
                const auto message = std::accumulate(first, first + count, std::string(), [](std::string result, auto&& value)
                {
                     return std::move(result) + ' ' + value;
                });
                spdlog::info("top five: {}", message);
            }
        }
    }
    catch (const boost::system::system_error& ex)
    {
        if (ex.code() != boost::asio::error::eof)
        {
            throw;
        }

        spdlog::info("No more numbers to receive");
    }
    catch (const std::exception& ex)
    {
        spdlog::error("Exception: {}", ex.what());
    }

    return 0;
}
