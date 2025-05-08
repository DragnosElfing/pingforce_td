#include "objects/entities/projectiles/snowball.hpp"
#include "objects/entities/towers/snowballer.hpp"
#include "objects/entities/towers/iciclestabber.hpp"
#include "utils/logger.hpp"

using namespace pftd;

/// Snowballer
Snowballer::Snowballer(utils::Vec2f const& position, int zIndex):
    Tower{"res/images/penguins/snowballer_peng.png", 1.1f, position, {170, 170}, zIndex}
{
    price = 100U;
    attackRangePixel = 400.0f;
    id = TowerID::SNOWBALLER;
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
    Tower{"res/images/penguins/iciclestabber_peng.png", 0.85f, position, {170, 170}, zIndex}
{
    price = 150U;
    attackRangePixel = 150.0f;
    instantAttack = true;
    id = TowerID::ICICLE_STABBER;
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
