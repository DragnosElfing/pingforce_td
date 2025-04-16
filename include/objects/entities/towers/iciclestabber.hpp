#pragma once

#include "objects/entities/towers/tower_base.hpp"

namespace pftd {

class IcicleStabber final : public Tower
{
public:
    IcicleStabber(utils::Vec2f const& position, int zIndex = 0);
    IcicleStabber();
    ~IcicleStabber() = default;
    
    Tower* clone() const override;
    void update(float dt) override;
};

}