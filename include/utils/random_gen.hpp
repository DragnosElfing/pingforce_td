#pragma once

#include "all.hpp"

namespace pftd {
namespace utils {

class Random
{
public:
    Random() = delete;

    static std::default_random_engine randomEngine;

    template<typename RandomDist>
    static auto generate(RandomDist distribution)
    {
        return distribution(Random::randomEngine);
    }
};

}
}