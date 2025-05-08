#pragma once

#include "objects/entities/seals/mock_seal_base.hpp"

namespace pftd_test 
{

/*! Páncélos zombi kicsiny (teszt). */
class FZC : public Seal
{
public:
    FZC(FollowPath const& followpath);

    Seal* clone() const override;
    
};

}