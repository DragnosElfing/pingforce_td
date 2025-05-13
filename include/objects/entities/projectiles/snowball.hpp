#pragma once

#ifndef CPORTA

#include "objects/entities/projectiles/projectile_base.hpp"

namespace pftd {

/*! Hógolyó lövedék. */
class Snowball : public Projectile
{
public:
    /**
    * @brief A textúra hard code-olt.
    *
    * @param position Pozíció.
    * @param direction Irány.
    * @param speed Repülési gyorsaság.
    */
    Snowball(utils::Vec2f const& position, utils::Vec2f direction, float speed = 50.0f);

    Snowball* clone() const override;

};

}

#endif
