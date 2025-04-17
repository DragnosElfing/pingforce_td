#pragma once

#include "all.hpp"
#include "utils/hetero_collection.hpp"

namespace pftd {

using EndPoint = utils::Vec2f;

/*! Az ellenfelek által követett út. */
struct FollowPath : public utils::Container<EndPoint>
{
    FollowPath();
};

}