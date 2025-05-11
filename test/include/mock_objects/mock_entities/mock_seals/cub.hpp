#pragma once

#include "mock_objects/mock_entities/mock_seals/seal_base.hpp"

namespace pftd_test 
{

/*! Kicsiny (teszt). */
class Cub : public Seal
{
public:
    Cub(FollowPath const& followpath);

    Seal* clone() const override;
    
};

}