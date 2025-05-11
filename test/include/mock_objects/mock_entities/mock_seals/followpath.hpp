#pragma once

#include "utils/hetero_collection.hpp"

namespace pftd_test
{

using namespace pftd;

using EndPoint = utils::Vec2f;

/*! Az ellenfelek által követett út. */
struct FollowPath : public utils::Container<EndPoint>
{
    /**
    * @brief A `Level`, amihez tartozik, "építi fel."
    */
    FollowPath();
};

}