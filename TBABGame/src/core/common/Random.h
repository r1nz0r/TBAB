#pragma once
#include <random>

namespace TBAB
{
    class Random
    {
    public:
        Random() = delete;
        Random(const Random&) = delete;
        Random& operator=(const Random&) = delete;
        Random(Random&&) = delete;
        Random& operator=(Random&&) = delete;

        // Return random generated number in range of [min, max]
        static int Get(int min, int max)
        {
            static std::mt19937 generator(std::random_device{}());
            std::uniform_int_distribution<int> distribution(min, max);

            return distribution(generator);
        }
    };
} // namespace TBAB