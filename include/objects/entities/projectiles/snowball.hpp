#pragma once

#include "objects/entities/projectiles/projectile_base.hpp"

namespace pftd {

class Snowball : public Projectile
{
public:
    Snowball(utils::Vec2f const& position, utils::Vec2f direction, float speed = 50.0f);

    Entity* clone() const override;

};

}