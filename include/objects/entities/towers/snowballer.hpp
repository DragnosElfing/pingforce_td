#pragma once

#include "objects/entities/towers/tower_base.hpp"

namespace pftd {

/*! Hógolyó dobáló. */
class Snowballer final : public Tower
{
public:
    Snowballer(utils::Vec2f const& position, int zIndex = 0);
    Snowballer();
    ~Snowballer() = default;

    /**
    * @brief Egy dinamikus memóriában foglalt másolatot készít a toronyról.
    *
    * @return A másolat.
    */
    Tower* clone() const override;

    /**
    * @brief Update.
    *
    * @param dt Delta idő.
    */
    void update(float dt) override;

    /**
    * @brief Megtámadja a `Tower::target`-et, ha van.
    */
    void attack() override;
    
};

}