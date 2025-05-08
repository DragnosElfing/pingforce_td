#pragma once

#include "all.hpp"

namespace pftd_test
{

using namespace pftd;

/*! Teszteléshez használt programelem. */
class Object
{
public:
    Object() = default;
    Object(utils::Vec2f position, utils::Vec2f size, int zIndex = 0):
        zIndex{zIndex}, position{position}, size{size}
    {}
    Object(Object const&) = default;
    Object(Object&&) noexcept = default;
    virtual ~Object() = default;

    virtual void draw() const = 0;

    struct Compare
    {
        bool operator()(Object const& o1, Object const& o2) const
        {
            return o1.zIndex > o2.zIndex;
        };

        bool operator()(Object const* o1, Object const* o2) const
        {
            return this->operator()(*o1, *o2);
        };
    };

//protected:
    int zIndex = 0;
    utils::Vec2f position;
    utils::Vec2f size;

};

}