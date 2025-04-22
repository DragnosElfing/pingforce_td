#pragma once

#include "objects/entities/entity_base.hpp"
#include "objects/entities/seals/followpath.hpp"
#include "utils/substitute_types.hpp"

namespace pftd 
{

/*! Fóka. */
class Seal : public Entity
{
public:
    /*! Éppen lopás közben van e? */
    bool isCurrentlyStealing = false;

    /*! HP. */
    int hp;

    /*! Gyorsaság. */
    float speed;

    /*! Pénz amit ad halál után. */
    unsigned int value; 

    virtual ~Seal() = default;

    /**
    * @brief LERP paraméter frissítése.
    *
    * A `followPath` pontjai közt lineárisan interpolál.
    */
    void lerpPath();
    
    /**
    * @brief Egy dinamikus memóriában foglalt másolatot készít a fókából.
    *
    * @return A másolat.
    */
    virtual Seal* clone() const override = 0;

    /**
    * @brief Update.
    *
    * @param dt Delta idő.
    */
    void update(float dt) override;

    /**
    * @brief `returned` getter.
    *
    * @return Elment e a fészekig és vissza a kezdőhelyre.
    */
    bool hasCompletedPath() const { return returned; }

    /**
    * @brief `reachedNest` getter.
    *
    * @return Elment e a fészekig.
    */
    bool hasReachedNest() const { return reachedNest; }

    /**
    * @brief Lesebzés.
    *
    * @param hpLost Ennyi HP-ja fog lemenni a fókának.
    */
    void damage(int hpLost = 1);

protected:
    /**
    * @brief
    *
    * @param followPath Az útvonal, amit követnie kell.
    * @param spriteSrc A sprite-jának az elérési útvonala.
    * @param size Méret.
    * @param hp HP.
    * @param speed Gyorsaság.
    * @param value Érték: ennyi pénzt kap a játékos ha megöli.
    * @param zIndex Z koordináta.
    */
    Seal(FollowPath const& followPath, std::string const& spriteSrc, utils::Vec2f const& size, int hp, float speed, unsigned int value, int zIndex = 0);
    
    /*! Az útvonal amin végigmegy. */
    FollowPath const& followPath;
    
    // Interpolációhoz

    /*! 0-tól 1-ig terjedő paraméter az interpolációhoz. */
    float lerpParam = 0.0f;

    /*! Elérte e a fészket. */
    bool reachedNest = false;

    /*! Visszatért e a kezdő ponthoz. */
    bool returned = false;

    /*! A következő pont az útvonalon. */
    EndPoint nextPoint;

private:
    /**
    * @brief Animáció: képkocka léptetése. 
    */
    void advanceAnimationFrame() override;

};

}