#ifndef PRIMES_SESSION_HPP
#define PRIMES_SESSION_HPP

#include <memory>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>

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
            , _outgoing(0)
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
                [this, self](boost::system::error_code error, std::size_t /*length*/)
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
            _primes = prime_generator::get_primes(_requested.value());
            send_next_prime();
        }

        void send_next_prime()
        {
            if (!_primes.empty())
            {
                _outgoing = utils::make_packed(_primes.front());
                _primes.pop_front();
                std::this_thread::sleep_for(std::chrono::microseconds(1000));

                boost::asio::async_write(_socket, boost::asio::buffer(_outgoing.data(), _outgoing.size()),
                    [this, self = shared_from_this()](boost::system::error_code error, std::size_t /*length*/)
                    {
                        if (!error)
                        {
                            send_next_prime();
                        }
                    }
                );
            }
        }

    private:
        boost::asio::ip::tcp::socket _socket;
        utils::packed<std::uint64_t> _requested;
        std::list<std::uint64_t>     _primes;
        utils::packed<std::uint64_t> _outgoing;
    };
}

#endif //PRIMES_SESSION_HPP
