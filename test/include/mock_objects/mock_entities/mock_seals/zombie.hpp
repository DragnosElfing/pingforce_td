#pragma once

#include "mock_objects/mock_entities/mock_seals/seal_base.hpp"

namespace pftd_test 
{

/*! Zombi fóka (teszt). */
class ZombieSeal : public Seal
{
public:
    ZombieSeal(FollowPath const& followpath);

    Seal* clone() const override;
    
};

}