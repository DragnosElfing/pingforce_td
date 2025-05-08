#pragma once

#include "objects/entities/towers/mock_tower_base.hpp"

namespace pftd_test 
{

using namespace pftd;

/*! Hógolyó dobáló (teszt). */
class Snowballer final : public Tower
{
public:
    Snowballer(utils::Vec2f const& position, int zIndex = 0);
    Snowballer();
    ~Snowballer() = default;

    Tower* clone() const override;
    void update(float dt) override;
    void attack() override;

    void serialize(std::ostream& out) const override;
    ;
    
};

}