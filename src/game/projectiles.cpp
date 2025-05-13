#ifndef CPORTA

#include "all.hpp"

#include "objects/entities/projectiles/projectile_base.hpp"
#include "objects/entities/projectiles/snowball.hpp"

using namespace pftd;

/// Snowball
Snowball::Snowball(utils::Vec2f const& position, utils::Vec2f direction, float speed):
    Projectile{"res/images/projectiles/snowball.png", position, {64, 64}, direction, speed, 1.0f}
{
    this->id = ProjectileID::SNOWBALL;
}

Snowball* Snowball::clone() const
{
    return new Snowball{position, direction, linearSpeed};
}
///

#endif
