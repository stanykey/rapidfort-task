#ifndef PRIMES_IO_HPP
#define PRIMES_IO_HPP

#include <istream>


namespace utils
{
    template <typename T>
    T read(std::istream& input)
    {
        T value{};
        input >> value;
        return value;
    }
}

#endif //PRIMES_IO_HPP
