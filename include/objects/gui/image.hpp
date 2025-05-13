#pragma once

#ifndef CPORTA

#include "all.hpp"

#include "objects/object_base.hpp"

namespace pftd {
namespace gr {

/*! Saját sprite osztály. Használható kép GUI elemként. */
class Sprite final : public Object
{
public:
    Sprite(sf::Texture const& texture, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex = -1);
    Sprite(sf::Texture const& texture, sf::IntRect const& textureRect, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex = -1);
    Sprite(std::string const& imageSrc, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex = -1);

    Sprite(Sprite const& other);
    Sprite(Sprite&& other) noexcept;

    ~Sprite() = default;

    /**
    * @brief Sprite szín modulációjának beállítása.
    *
    * Megjegyzés: Az SFML által biztosított modulációt használja.
    *
    * @param color Szín, amivel szorzunk.
    */
    void modColor(sf::Color const& color);

    /**
    * @brief Y tengely mentén tükröz.
    *
    * Nincs használva.
    */
    void flipY();

    /**
    * @brief Nyújt.
    *
    * @param factor Ennyivel nyújt az X-Y tengelyek mentén.
    */
    void scale(utils::Vec2f const& factor);

    /**
    * @brief A textúra csak egy részletének használata Sprite-ként.
    *
    * @param textureRect A tárolt textúra része egy téglalappal megadva.
    */
    void setSpriteRect(sf::IntRect const& textureRect);

    /**
    * @brief Beállítja az `m_sprite` pozícióját.
    *
    * @param newPos Az új pozíció.
    */
    void setPosition(utils::Vec2f const& newPos) { m_sprite.setPosition({newPos.x, newPos.y}); }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    /*! Sprite-hoz tartozó textúra. */
    sf::Texture const& m_texture;

    /*! Sprite. */
    sf::Sprite m_sprite;

};

}
}

#endif
