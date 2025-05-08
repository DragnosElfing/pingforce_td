#pragma once

#include "objects/entities/seals/mock_seal_base.hpp"

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