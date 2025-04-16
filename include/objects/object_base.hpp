#pragma once

#include "all.hpp"

namespace pftd
{

class Object : public sf::Drawable
{
public:
    Object() = default;
    Object(utils::Vec2f position, utils::Vec2f size, int zIndex = 0):
        zIndex{zIndex}, position{position}, size{size}
    {}
    Object(Object const&) = default;
    Object(Object&&) noexcept = default;
    virtual ~Object() = default;

    //virtual Object* clone() const = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

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

protected:
    int zIndex = 0;
    utils::Vec2f position;
    utils::Vec2f size;

};

}