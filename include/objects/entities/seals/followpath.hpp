#pragma once

#include <vector>
#include "utils/hetero_collection.hpp"
#include "utils/substitute_types.hpp"

namespace pftd {

struct FollowPath : public utils::HCollection<utils::Vec2f>
{
    float followerSpeed = 15.0f;   
    FollowPath();
};

}