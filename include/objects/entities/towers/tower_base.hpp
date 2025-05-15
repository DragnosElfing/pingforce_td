#pragma once

#ifndef CPORTA

#include "objects/entities/entity_base.hpp"
#include "objects/entities/projectiles/projectile_base.hpp"
#include "objects/entities/seals/seal_base.hpp"
#include "utils/serializable.hpp"

namespace pftd {

enum class TowerID
{
    SNOWBALLER = 0,
    ICICLE_STABBER
};

/*! Torony (pingvin) ősosztály. */
class Tower : public Entity, public utils::Serializable
{
    using ProjSpawnFunc = std::function<void(Projectile*)>;
public:
    struct TowerProperties
    {
        TowerID id;

        /*! Az a környezete, amibe másik tornyot nem lehet lehelyezni. */
        float radiusPixel = 120.0f;

        /*! Az a környezete, amiben célpontot keres. */
        float attackRangePixel = 100.0f;

        /*! Támadás gyorsasága. */
        float attackSpeedSec = 1.0f;

        /*! Támadás ereje: mennyi HP-t visz le. */
        unsigned int attackDamage = 1U;

        /*! Instant támadó (true)? Vagy lövedékkel (false)?*/
        bool instantAttack = false;

        /*! Az ára, amikor az "eszköztárban" van. */
        unsigned int price = 0U;

        TowerProperties(TowerID id, float radius = 120.0f, float attackRange = 100.0f, float attackSpeed = 1.0f,
            unsigned int attackDamage = 1U, bool instant = false, unsigned int price = 0U);

    } properties;

    Tower(TowerProperties const& props, std::string const& spriteSheetSrc, utils::Vec2i spriteSize, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex = 0);
    Tower(TowerProperties const& props, std::string const& spriteSrc, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex = 0);
    Tower(Tower const& other);
    virtual ~Tower() = default;

    /**
    * @brief Lövedék kilövéséhez használt callback függvény beállítása
    *
    * @param callback A függvény.
    */
    void setProjSpawnCb(ProjSpawnFunc callback);

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

    virtual void update(float dt) override;

    void serialize(std::ostream& out) const override;

protected:
    /*! Célpont. */
    Seal* target = nullptr;

    /*! Callback függvény, ha a torony távolsági (valamit kilő). */
    ProjSpawnFunc spawnProjectile;

    /*! Támadások közti idő mérésére szolgáló számláló. */
    float attackTimerSec = 0.0f;

    void advanceAnimationFrame() override;
};

}

#endif
