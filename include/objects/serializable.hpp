#pragma once

#include "all.hpp"

namespace pftd {

/*! Szérializálható osztályok. */
class Serializable 
{
public:
    /**
    * @brief Kiír egy streamre.
    *
    * @param out A stream.
    */
    virtual void serialize(std::ostream& out) = 0;

    /**
    * @brief Beolvas egy streamről.
    *
    * @param out A stream.
    */
    virtual void deserialize(std::istream& in) = 0;
};

}