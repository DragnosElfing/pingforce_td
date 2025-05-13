#pragma once

#include "all.hpp"

namespace pftd {
namespace utils {

/*! Szérializálható osztályok. */
class Serializable
{
public:
    /**
    * @brief Kiír egy streamre.
    *
    * @param out A stream.
    */
    virtual void serialize(std::ostream& out) const = 0;

    /**
    * @brief Beolvas egy streamről.
    *
    * Megjegyzés: nincs használva, a `SaveFileParser` intézi a neki szánt munkát.
    *
    * @param in A stream.
    */
    //virtual void deserialize(std::istream& in) = 0;
};

}
}
