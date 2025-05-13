#pragma once

#ifndef CPORTA

#include "objects/entities/seals/seal_base.hpp"

namespace pftd {

/*! Kicsiny. */
class Cub : public Seal
{
public:
    /**
    * @brief A textúra hard code-olt, a kezdő pozíciót pedig a `followPath` határozza meg.
    *
    * @param followpath Az útvonal amin végig kell menjen (majd pedig vissza).
    */
    Cub(FollowPath const& followpath);

    Seal* clone() const override;

};

}

#endif
