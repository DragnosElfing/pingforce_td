#pragma once

#include "all.hpp"
#include "utils/hetero_collection.hpp"

namespace pftd {

struct FollowPath : public utils::HCollection<utils::Vec2f>
{
    //float followerSpeed = 50.0f;   
    FollowPath();
};

}