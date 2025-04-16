#pragma once

#include "objects/entities/seals/seal_base.hpp"

namespace pftd {

class RegularSeal : public Seal
{
public:
    RegularSeal(FollowPath const& followpath);

    Seal* clone() const override;
};

}