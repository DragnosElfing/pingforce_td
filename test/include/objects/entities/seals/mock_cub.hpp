#pragma once

#include "objects/entities/seals/mock_seal_base.hpp"

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