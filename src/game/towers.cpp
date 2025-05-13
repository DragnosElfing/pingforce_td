#ifndef CPORTA

#include "objects/entities/projectiles/snowball.hpp"
#include "objects/entities/towers/snowballer.hpp"
#include "objects/entities/towers/iciclestabber.hpp"
#include "utils/logger.hpp"

using namespace pftd;

/// Snowballer
Snowballer::Snowballer(utils::Vec2f const& position, int zIndex):
    Tower{{
        TowerID::SNOWBALLER,
        120.0f, 400.0f, 1.1f, 1U, false,
        100U
    }, "res/images/penguins/snowballer_peng.png", position, {170, 170}, zIndex}
{

}

Snowballer::Snowballer():
    Snowballer{{-1000, -1000}, 1}
{

}

Tower* Snowballer::clone() const
{
    return new Snowballer{position, zIndex};
}

void Snowballer::update(float dt)
{
    Tower::update(dt);
}

void Snowballer::attack()
{
    if(target) {
        this->spawnProjectile(new Snowball{position, (target->getPosition() - position).normalize(), 300.0f});
    }
    Tower::attack();
}
///

/// Icicle Stabber
IcicleStabber::IcicleStabber(utils::Vec2f const& position, int zIndex):
    Tower{{
        TowerID::ICICLE_STABBER,
        120.0f, 150.0f, 0.15f, 1U, true,
        150U
    }, "res/images/penguins/iciclestabber_peng.png", position, {170, 170}, zIndex}
{

}

IcicleStabber::IcicleStabber():
    IcicleStabber{{-1000, -1000}, 1}
{

}

Tower* IcicleStabber::clone() const
{
    return new IcicleStabber{position, zIndex};
}

void IcicleStabber::update(float dt)
{
    Tower::update(dt);
}

///

#endif
