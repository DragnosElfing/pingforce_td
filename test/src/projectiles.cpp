#include "all.hpp"

#include "mock_objects/mock_entities/mock_projectiles/projectile_base.hpp"
#include "mock_objects/mock_entities/mock_projectiles/snowball.hpp"

using namespace pftd_test;

/// Snowball
Snowball::Snowball(utils::Vec2f const& position, utils::Vec2f direction, float speed):
    Projectile{"res/images/projectiles/snowball.png", position, {64, 64}, direction, speed, 1.0f}
{
    this->id = ProjectileID::SNOWBALL;
}

Projectile* Snowball::clone() const
{
    return new Snowball{position, direction, linearSpeed};
}
///
