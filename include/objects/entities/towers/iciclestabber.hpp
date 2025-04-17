#pragma once

#include "objects/entities/towers/tower_base.hpp"

namespace pftd {

/*! Jégcsap kardos. */
class IcicleStabber final : public Tower
{
public:
    IcicleStabber(utils::Vec2f const& position, int zIndex = 0);
    IcicleStabber();
    ~IcicleStabber() = default;
    
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
};

}