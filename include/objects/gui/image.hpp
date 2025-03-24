#pragma once

#include "SFML/Graphics.hpp"

#include "objects/object_base.hpp"
#include "resources.hpp"
#include "utils/logger.hpp"

namespace pftd {
// TODO: rename to gr
namespace gui {

// TODO: rename to Sprite
class Image : public Object
{
public:
    Image(std::string const&, sf::Vector2i const&, sf::Vector2i const&, int yIndex = -1);
    Image(sf::Texture const&, sf::Vector2i const&, sf::Vector2i const&, int yIndex = -1);
    Image(sf::Texture const&, sf::IntRect const&, sf::Vector2i const&, sf::Vector2i const&, int yIndex = -1);
    Image(Image const&);
    Image(Image&&) noexcept;
    ~Image() = default;

    void modColor(sf::Color const&);
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
    void setSpriteRect(sf::IntRect const&);

private:
    sf::Texture m_texture; // TODO: should be a pointer
    sf::Sprite m_sprite;
};

}
}