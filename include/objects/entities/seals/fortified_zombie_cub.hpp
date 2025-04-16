#pragma once

#include "objects/entities/seals/seal_base.hpp"

namespace pftd {

class FZC : public Seal
{
public:
    FZC(FollowPath const& followpath);

    Seal* clone() const override;
};

}