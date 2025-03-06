#pragma once

#include "SFML/Graphics/Drawable.hpp"

namespace pftd
{

class Object : public sf::Drawable
{
public:
    Object() = default;
    virtual ~Object() = default;

    virtual void draw(sf::RenderTarget&, sf::RenderStates) const = 0;

    struct Compare
    {
        bool operator()(Object const& o1, Object const& o2) const
        {
            return o1.yIndex > o2.yIndex;
        };

        bool operator()(Object const* o1, Object const* o2) const
        {
            return this->operator()(*o1, *o2);
        };
    };

protected:
    int yIndex = 0;

private:

};

}