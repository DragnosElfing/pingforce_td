#pragma once

#include "utils/hetero_collection.hpp"

namespace pftd_test {

using namespace pftd;

using EndPoint = utils::Vec2f;

struct FollowPath : public utils::Container<EndPoint>
{
    FollowPath() = default;
};

}