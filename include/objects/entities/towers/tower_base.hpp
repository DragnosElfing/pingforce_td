#pragma once

#include "objects/entities/entity_base.hpp"
#include "objects/entities/projectiles/projectile_base.hpp"
#include "objects/entities/seals/seal_base.hpp"

namespace pftd {

/*! Torony (pingvin). */
class Tower : public Entity
{
    using ProjSpawnFunc = std::function<void(Projectile*)>;
public:
    /*! Az a környezete, amibe másik tornyot nem lehet lehelyezni. */
    float radiusPixel = 120.0f;

    /*! Az a környezete, amiben célpontot keres. */
    float attackRangePixel = 100.0f;

    /*! Támadás gyorsasága. */
    float attackSpeedSec;

    /*! Támadás ereje: mennyi HP-t visz le. */
    unsigned int attackDamage = 1U;

    /*! Az ára, amikor az "eszköztárban" van. */
    unsigned int price = 0U;

    /*! Instant támadó (true)? Vagy lövedékkel (false)?*/
    bool instantAttack = false;

    // TODO: config struct for the data above as a param
    Tower(std::string const& spriteSheetSrc, utils::Vec2i spriteSize, float attackSpeedSec, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex = 0);
    Tower(std::string const& spriteSrc, float attackSpeedSec, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex = 0);
    Tower(Tower const&);
    virtual ~Tower() = default;

    /**
    * @brief Lövedék kilövéséhez használt callback függvény beállítása
    *
    * @param callback A függvény.
    */
    void setProjSpawnCb(ProjSpawnFunc callback);

    /**
    * @brief Egy dinamikus memóriában foglalt másolatot készít a toronyról.
    *
    * @return A másolat.
    */
    virtual Tower* clone() const override = 0;

    /**
    * @brief Megtámadja a `target`-et, ha van.
    */
    virtual void attack();

    /**
    * @brief Megfelelő célpontot keres.
    *
    * Megjegyzés: csak akkor keres, ha a `target` egy nullptr.
    *
    * @param enemies Ellenfelek, amik közt célpontot keres.
    */
    virtual bool lookForTarget(std::vector<Seal*> const& enemies);

    /**
    * @brief Update.
    *
    * @param dt Delta idő.
    */
    virtual void update(float dt) override;

protected:
    /*! Célpont. */
    Seal* target = nullptr;

    /*! Callback függvény, ha a torony távolsági (valamit kilő). */
    ProjSpawnFunc spawnProjectile;

    /*! Támadások közti idő mérésére szolgáló számláló. */
    float attackTimerSec = 0.0f;

    /**
    * @brief Animáció: képkocka léptetése. 
    */
    void advanceAnimationFrame() override;
};

}