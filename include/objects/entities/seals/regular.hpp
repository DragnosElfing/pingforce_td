#pragma once

#ifndef CPORTA

#include "objects/entities/seals/seal_base.hpp"

namespace pftd {

/*! "Normális" fóka. */
class RegularSeal : public Seal
{
public:
    /**
    * @brief
    *
    * @param followpath Az útvonal amin végig kell menjen (majd pedig vissza).
    */
    RegularSeal(FollowPath const& followpath);

    Seal* clone() const override;

};

}

#endif
