#pragma once

#include "objects/entities/seals/seal_base.hpp"

namespace pftd {

class ZombieSeal : public Seal
{
public:
    ZombieSeal(FollowPath const& followpath);

    Seal* clone() const override;
};

}