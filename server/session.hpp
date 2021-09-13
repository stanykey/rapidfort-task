#ifndef PRIMES_SESSION_HPP
#define PRIMES_SESSION_HPP

#include <memory>
#include <string>
#include <sstream>

#include <boost/asio.hpp>

#include <core/prime_generator.hpp>
#include <utils/packed.hpp>


namespace primes
{
    class session : public std::enable_shared_from_this<session>
    {
    public:
        explicit session(boost::asio::ip::tcp::socket socket)
            : _socket(std::move(socket))
            , _requested(0)
        {
        }

        void start()
        {
            read_request();
        }

    private:
        void read_request()
        {
            auto self(shared_from_this());
            _socket.async_read_some(boost::asio::buffer(_requested.data(), _requested.size()),
                [this, self](boost::system::error_code error, std::size_t length)
                {
                    if (!error)
                    {
                        process_request();
                    }
                }
            );
        }

        void process_request()
        {
            auto self(shared_from_this());
            auto primes = prime_generator::get_primes(_requested.value());
            while (!primes.empty())
            {
                auto prime = new utils::packed<std::size_t>(primes.front());
                boost::asio::async_write(_socket, boost::asio::buffer(prime->data(), prime->size()),
                    [self, prime](boost::system::error_code error, std::size_t /*length*/)
                    {
                        delete prime;
                    }
                );
                primes.pop_front();
            }
        }

        boost::asio::ip::tcp::socket _socket;
        utils::packed<std::uint64_t> _requested;
    };
}

#endif //PRIMES_SESSION_HPP
