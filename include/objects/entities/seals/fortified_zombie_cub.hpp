#pragma once

#include "objects/entities/seals/seal_base.hpp"

namespace pftd {

/*! Páncélos zombi kicsiny. */
class FZC : public Seal
{
public:
    /**
    * @brief
    *
    * @param followpath Az útvonal amin végig kell menjen (majd pedig vissza).
    */
    FZC(FollowPath const& followpath);

    /**
    * @brief Egy dinamikus memóriában foglalt másolatot készít a fókából.
    *
    * @return A másolat.
    */
    Seal* clone() const override;
    
};

}