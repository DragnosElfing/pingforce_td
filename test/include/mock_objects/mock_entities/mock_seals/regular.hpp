#pragma once

#include "mock_objects/mock_entities/mock_seals/seal_base.hpp"

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