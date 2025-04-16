#pragma once

#include "objects/entities/entity_base.hpp"
#include "utils/substitute_types.hpp"

namespace pftd {
    
class Projectile : public Entity
{
public:
    utils::Vec2f direction; // Normalizált!
    float linearSpeed;
    float angularSpeedRadPerSec;

    virtual ~Projectile() = default;
    virtual void update(float dt) override;

protected:
    Projectile(std::string const& spriteSrc, utils::Vec2f const& position, 
        utils::Vec2f const& size, utils::Vec2f const& direction, float speed, float angularSpeed = 0.0f, int zIndex = 0);

};

}