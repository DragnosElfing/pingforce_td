#pragma once

#include "objects/entities/entity_base.hpp"
#include "utils/substitute_types.hpp"

namespace pftd {
    
class Projectile : public Entity
{
public:
    /*! Irány (normalizált). */
    utils::Vec2f direction;

    /*! Lineáris gyorsaság. */
    float linearSpeed;

    /*! Forgási sebesség. */
    float angularVelocityRadPerSec;

    virtual ~Projectile() = default;

    /**
    * @brief Update.
    *
    * @param dt Delta idő.
    */
    virtual void update(float dt) override;

protected:
    /**
    * @brief
    *
    * @param spriteSrc Sprite eleérési útvonal.
    * @param position Pozíció.
    * @param size Méret.
    * @param direction Irány.
    * @param speed Lineáris gyorsaság.
    * @param angularSpeed Forgási sebesség (radián / mp).
    * @param zIndex Z koordináta.
    */
    Projectile(std::string const& spriteSrc, utils::Vec2f const& position, 
        utils::Vec2f const& size, utils::Vec2f const& direction, float speed, float angularSpeed = 0.0f, int zIndex = 0);

};

}