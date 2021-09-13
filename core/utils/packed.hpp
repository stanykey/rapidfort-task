//
// Created by Admin on 9/14/2021.
//

#ifndef PRIMES_PACKED_HPP
#define PRIMES_PACKED_HPP


namespace utils
{
    template <typename T>
    struct packed
    {
    public:
        explicit packed(T value)
            : _data{value}
        {
        }

        [[nodiscard]] void* data()
        {
            return reinterpret_cast<void*>(&_data);
        }

        [[nodiscard]] const void* data() const
        {
            return reinterpret_cast<const void*>(&_data);
        }

        [[nodiscard]] std::size_t size() const
        {
            return sizeof(T);
        }


        [[nodiscard]] T value() const
        {
            return _data;
        }

        [[nodiscard]] explicit operator T() const
        {
            return _data;
        }

    private:
        T _data;
    };


    template <typename T>
    packed<T> make_packed(T value)
    {
        return packed<T>(value);
    }
}

#endif //PRIMES_PACKED_HPP
