#pragma once

#include "SFML/Graphics.hpp"

#include "objects/object_base.hpp"
#include "utils/substitute_types.hpp"

namespace pftd {
namespace gr {

class Sprite final : public Object
{
public:
    Sprite(sf::Texture const& texture, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex = -1);
    Sprite(sf::Texture const& texture, sf::IntRect const& textureRect, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex = -1);
    Sprite(std::string const& imageSrc, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex = -1);
    Sprite(Sprite const& other);
    Sprite(Sprite&& other) noexcept;
    ~Sprite() = default;

    void modColor(sf::Color const& color);
    void setSpriteRect(sf::IntRect const& textureRect);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

//private:
    sf::Texture m_texture; // ? TODO: should be a pointer
    sf::Sprite m_sprite;

};

}
}