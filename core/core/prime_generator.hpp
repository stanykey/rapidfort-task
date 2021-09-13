#ifndef PRIMES_PRIME_GENERATOR_HPP
#define PRIMES_PRIME_GENERATOR_HPP

#include <vector>
#include <list>


namespace primes
{
    struct prime_generator
    {
        static std::list<std::uint64_t> get_primes(const std::uint64_t upper_bound)
        {
            std::list<std::uint64_t> primes;

            std::vector<bool> sieve(upper_bound + 1, true);
            sieve[0] = false;
            sieve[1] = false;
            std::uint64_t curr_num = 2;
            while (curr_num * curr_num <= upper_bound)
            {
                for (auto idx = curr_num * curr_num; idx <= upper_bound; idx += curr_num)
                {
                    sieve[idx] = false;
                }
                ++curr_num;
            }

            for (std::uint64_t idx = 2; idx <= upper_bound; ++idx)
            {
                if (sieve[idx])
                {
                    primes.push_back(idx);
                }
            }
            return primes;
        }
    };
}

#endif //PRIMES_PRIME_GENERATOR_HPP
