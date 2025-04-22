#pragma once

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

    /**
    * @brief Egy dinamikus memóriában foglalt másolatot készít az entitásról.
    *
    * @return A másolat.
    */
    Entity* clone() const override;

};

}