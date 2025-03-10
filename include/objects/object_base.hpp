#pragma once

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/System/Vector2.hpp"

namespace pftd
{

class Object : public sf::Drawable
{
public:
    Object() = default;
    Object(sf::Vector2i const& position, sf::Vector2i const& size, int yIndex = 0):
        yIndex{yIndex}, position{position}, size{size}
    {}
    Object(Object const&) = default;
    Object(Object&&) noexcept = default;
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
    sf::Vector2i position = {0, 0};
    sf::Vector2i size = {0, 0};

private:

};

}