#pragma once

#include "objects/entities/entity_base.hpp"

namespace pftd {

class Tower : public Entity
{
public:
    float radiusPixel = 120.0f;
    float attackRangePixel = 100.0f;
    float attackSpeedSec = 0.8f;
    unsigned int attackDamage = 1U;
    unsigned int price = 0U;

    Tower(std::string const& spriteSheetSrc, utils::Vec2i spriteSize, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex = 0);
    Tower(std::string const& spriteSrc, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex = 0);
    Tower(Tower const&);
    virtual ~Tower() = default;

    virtual void attack(bool instant = false);

protected:
    Entity const* target = nullptr;

    virtual Entity const* lookForTarget(/* Entity** entities */) const;

};

}