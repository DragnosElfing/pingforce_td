#pragma once

#include "all.hpp"

#include "objects/gui/image.hpp"
#include "objects/object_base.hpp"
#include "objects/serializable.hpp"

namespace pftd {

/*! Mindenféle "actor" ősosztálya: tornyok, fólák és lövedékek. */
class Entity : public Object, public Serializable
{
public:
    /*! Animált e? */
    bool isAnimated = true;

    Entity(std::string const& spriteSheetSrc, utils::Vec2i spriteSize, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex = 0);
    Entity(sf::Texture const& texture, utils::Vec2i spriteSize, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex = 0);
    Entity(std::string const& spriteSrc, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex = 0);
    Entity(Entity const& other);
    virtual ~Entity();

    /**
    * @brief Egy dinamikus memóriában foglalt másolatot készít az entitásról.
    *
    * @return A másolat.
    */
    virtual Entity* clone() const = 0;

    /**
    * @brief Update.
    *
    * @param dt Delta idő.
    */
    virtual void update(float dt);

    /**
    * @brief Objektum megjelenítése.
    *
    * @param target Hol legyen megjelenítve? Ez általában egy ablak.
    * @param states Render-eléshez szükséges egyéb állapotok.
    */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    /**
    * @brief Pozíció beállítása.
    *
    * @param position Az új pozíció. 
    */
    void setPosition(utils::Vec2f position);

    /**
    * @brief `position` getter.
    *
    * @return Az entitás jelenlegi pozíciója.
    */
    auto getPosition() const { return position; }
    
    /**
    * @brief Konstans `currentSprite` getter.
    *
    * @return A jelenlegi sprite.
    */
    gr::Sprite const* getSprite() const { return currentSprite; }

    /**
    * @brief `currentSprite` getter.
    *
    * @return A jelenlegi sprite.
    */
    gr::Sprite* getSprite() { return currentSprite; }

protected:
    /*! A sprite sheet. */
    sf::Texture const& spriteSheet; // Feltételezzük, hogy egy sorban vannak a sprite-ok
    
    /*! Képkockák mérete (fix). */
    utils::Vec2i cellSize;

    /*! Képkockák száma. */
    size_t const CELL_N;

    /*! A sprite sheet aktív képkockája. */
    size_t currentCell = 0U;

    /*! A jelenlegi képkocka által meghatározott sprite. */
    gr::Sprite* currentSprite = nullptr;

    /*! Ennyi ideig "tart" egy képkocka, ezután váltani kell. */
    float frameDurationSec = 1.0f;

    /*! Eddig eltelt idő. */
    float totalElapsedSec = 0.0f; // Animációhoz van használva elsősorban.

    /**
    * @brief Animáció: képkocka léptetése. 
    */
    virtual void advanceAnimationFrame();

};

}