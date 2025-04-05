#pragma once

#include "objects/entities/towers/tower_base.hpp"

namespace pftd {

class Snowballer final : public Tower
{
public:
    Snowballer(utils::Vec2f const& position, int zIndex = 0);
    Snowballer();
    ~Snowballer() = default;

    void update(float dt);
    
};

}