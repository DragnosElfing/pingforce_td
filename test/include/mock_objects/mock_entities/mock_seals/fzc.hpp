#pragma once

#include "mock_objects/mock_entities/mock_seals/seal_base.hpp"

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