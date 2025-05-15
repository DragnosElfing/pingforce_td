#pragma once

#include "mock_objects/mock_entities/mock_towers/tower_base.hpp"

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
    
};

}