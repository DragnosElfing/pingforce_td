#pragma once

#include "all.hpp"

namespace pftd {
namespace utils {

/*! Random szám generáláshoz használt segédosztály. Ez egy teljesen statikus osztály. */
class Random
{
public:
    Random() = delete;

    /*! Felhasznált random engine. (Az alapértelmezett.) */
    static std::default_random_engine randomEngine;

    /**
    * @brief Random szám generálása megadott eloszlás szerint.
    *
    * @param distribution Generálandó számok eloszlása.
    * @return Generált szám.
    */
    template<typename RandomDist>
    static auto generate(RandomDist distribution)
    {
        return distribution(randomEngine);
    }
};

}
}