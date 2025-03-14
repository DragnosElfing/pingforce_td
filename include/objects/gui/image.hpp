#pragma once

#include "SFML/Graphics.hpp"

#include "objects/object_base.hpp"

namespace pftd {
namespace gui {

class Image : public Object
{
public:
    Image(std::string const&, sf::Vector2i const&, sf::Vector2i const&, int yIndex = -1);
    Image(sf::Texture const&, sf::Vector2i const&, sf::Vector2i const&, int yIndex = -1);
    Image(Image const&) = default;
    Image(Image&&) noexcept = default;
    ~Image() = default;

    void modColor(sf::Color const&);
    void draw(sf::RenderTarget&, sf::RenderStates) const override;

private:
    sf::Texture m_texture; // TODO: should be a pointer
    sf::Sprite m_sprite;
};

}
}