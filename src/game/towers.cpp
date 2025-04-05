#include "objects/entities/towers/snowballer.hpp"
#include "objects/entities/towers/iciclestabber.hpp"
#include "utils/logger.hpp"

using namespace pftd;

/// Snowballer
Snowballer::Snowballer(utils::Vec2f const& position, int zIndex):
    Tower{"res/images/penguins/snowballer_peng.png", position, {170, 170}, zIndex}
{
    price = 100U;
    attackSpeedSec = 1.5f;
}

Snowballer::Snowballer():
    Snowballer{{-1000, -1000}, 1}
{

}

void Snowballer::update(float dt)
{
    Entity::update(dt);
}
///

/// Icicle Stabber
IcicleStabber::IcicleStabber(utils::Vec2f const& position, int zIndex):
    Tower{"res/images/penguins/iciclestabber_peng.png", position, {170, 170}, zIndex}
{
    price = 150U;
    attackSpeedSec = 1.0f;
}

IcicleStabber::IcicleStabber():
    IcicleStabber{{-1000, -1000}, 1}
{

}

void IcicleStabber::update(float dt)
{
    Entity::update(dt);
}

///
