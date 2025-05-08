#pragma once

#include "objects/entities/seals/mock_seal_base.hpp"

namespace pftd_test 
{

/*! "Normális" fóka (teszt). */
class RegularSeal : public Seal
{
public:
    RegularSeal(FollowPath const& followpath);

    Seal* clone() const override;
    
};

}