#pragma once

#include "mock_objects/mock_entities/mock_projectiles/projectile_base.hpp"

namespace pftd_test 
{

using namespace pftd;

/*! Hógolyó lövedék (teszt). */
class Snowball : public Projectile
{
public:
    Snowball(utils::Vec2f const& position, utils::Vec2f direction, float speed = 50.0f);

    Entity* clone() const override;

};

}