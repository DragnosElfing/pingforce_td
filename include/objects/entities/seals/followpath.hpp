#pragma once

#ifndef CPORTA

#include "utils/hetero_collection.hpp"

namespace pftd {

using EndPoint = utils::Vec2f;

/*! Az ellenfelek által követett út. */
struct FollowPath : public utils::Container<EndPoint>
{
    /**
    * @brief A `Level` - amihez tartozik - "építi fel."
    */
    FollowPath() = default;
};

}

#endif
