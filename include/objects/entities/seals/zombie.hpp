#pragma once

#ifndef CPORTA

#include "objects/entities/seals/seal_base.hpp"

namespace pftd {

/*! Zombi fóka. */
class ZombieSeal : public Seal
{
public:
    /**
    * @brief
    *
    * @param followpath Az útvonal amin végig kell menjen (majd pedig vissza).
    */
    ZombieSeal(FollowPath const& followpath);

    Seal* clone() const override;

};

}

#endif
