#pragma once

#include "objects/entities/towers/mock_tower_base.hpp"

namespace pftd_test 
{

using namespace pftd;

/*! Jégcsap kardos (teszt). */
class IcicleStabber final : public Tower
{
public:
    IcicleStabber(utils::Vec2f const& position, int zIndex = 0);
    IcicleStabber();
    ~IcicleStabber() = default;

    Tower* clone() const override;
    void update(float dt) override;

    void serialize(std::ostream& out) const override;
    ;
};

}