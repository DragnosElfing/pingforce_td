#include "utils/random_gen.hpp"

using namespace pftd::utils;

auto Random::randomEngine = std::default_random_engine{std::random_device{}()};