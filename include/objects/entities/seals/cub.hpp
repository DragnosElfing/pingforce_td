#pragma once

#include "objects/entities/seals/seal_base.hpp"

namespace pftd {

class Cub : public Seal
{
public:
    Cub(FollowPath const& followpath);

    Seal* clone() const override;
};

}