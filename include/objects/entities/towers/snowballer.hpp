#pragma once

#ifndef CPORTA

#include "objects/entities/towers/tower_base.hpp"

namespace pftd {

/*! Hógolyó dobáló. */
class Snowballer final : public Tower
{
public:
    Snowballer(utils::Vec2f const& position, int zIndex = 0);
    Snowballer();
    ~Snowballer() = default;

    Tower* clone() const override;

    void update(float dt) override;

    /**
    * @brief Megtámadja a `Tower::target`-et, ha van.
    */
    void attack() override;

};

}

#endif
