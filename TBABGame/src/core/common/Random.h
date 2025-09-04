#pragma once
#include <random>

namespace TBAB
{
    /**
    * @class Random
    * @brief Static utility class for generating random numbers.
    * * Uses `std::mt19937` with `std::random_device` to produce high-quality
    * random numbers. The class cannot be instantiated.
    */
    class Random
    {
    public:
        Random() = delete;
        Random(const Random&) = delete;
        Random& operator=(const Random&) = delete;
        Random(Random&&) = delete;
        Random& operator=(Random&&) = delete;

        /**
        * @brief Returns a random number in the given range.
        * * @param min The lower bound of the range (inclusive).
        * @param max The upper bound of the range (inclusive).
        * @return int A random number in the range `min` to `max`.
        */
        static int Get(int min, int max)
        {
            static std::mt19937 generator(std::random_device{}());
            std::uniform_int_distribution<int> distribution(min, max);

            return distribution(generator);
        }
    };
} // namespace TBAB