#pragma once

#include "all.hpp"

#include "objects/object_base.hpp"

namespace pftd {
namespace gr {

#if not defined(_PFTD_TEST) && not defined(CPORTA)
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
    */
    void flipY();

    /**
    * @brief A textúra csak egy részletének használata Sprite-ként.
    *
    * @param textureRect A tárolt textúra része egy téglalappal megadva.
    */
    void setSpriteRect(sf::IntRect const& textureRect);

    /**
    * @brief Objektum megjelenítése.
    *
    * @param target Hol legyen megjelenítve? Ez általában egy ablak.
    * @param states Render-eléshez szükséges egyéb állapotok.
    */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

//private:
    /*! Sprite-hoz tartozó textúra. */
    sf::Texture const& m_texture;

    /*! Sprite. */
    sf::Sprite m_sprite;

};
#endif

/*! Teszteléshez szánt Sprite. */
class MockSprite final : public MockObject
{
public:
    // MockSprite(sf::Texture const& texture, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex = -1);
    // MockSprite(sf::Texture const& texture, sf::IntRect const& textureRect, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex = -1);
    MockSprite(std::string const& imageSrc, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex = -1);
    MockSprite(MockSprite const& other);
    MockSprite(MockSprite&& other) noexcept;
    ~MockSprite() = default;

    void modColor(uint8_t color);
    void setSpriteRect(utils::Vec2i const& textureRectStart, utils::Vec2i const& textureRectEnd);
    void draw() const override;

};

}
}