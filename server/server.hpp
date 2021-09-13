#ifndef PRIMES_SERVER_HPP
#define PRIMES_SERVER_HPP

#include "session.hpp"


namespace primes
{
    class server
    {
    public:
        server(boost::asio::io_context& io_context, std::uint16_t port)
            : _acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
        {
            do_accept();
        }

    private:
        void do_accept()
        {
            _acceptor.async_accept([this](boost::system::error_code error, boost::asio::ip::tcp::socket socket)
            {
                if (!error)
                {
                    std::make_shared<session>(std::move(socket))->start();
                }

                do_accept();
            });
        }

        boost::asio::ip::tcp::acceptor _acceptor;
    };
}

#endif //PRIMES_SERVER_HPP
