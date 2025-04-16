#pragma once

#include "objects/entities/entity_base.hpp"
#include "objects/entities/projectiles/projectile_base.hpp"
#include "objects/entities/seals/seal_base.hpp"

namespace pftd {

class Tower : public Entity
{
    using ProjSpawnFunc = std::function<void(Projectile*)>;
public:
    float radiusPixel = 120.0f;
    float attackRangePixel = 100.0f;
    float attackSpeedSec;
    unsigned int attackDamage = 1U;
    unsigned int price = 0U;
    bool instantAttack = false;

    // TODO: config struct for the data above as a param
    Tower(std::string const& spriteSheetSrc, utils::Vec2i spriteSize, float attackSpeedSec, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex = 0);
    Tower(std::string const& spriteSrc, float attackSpeedSec, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex = 0);
    Tower(Tower const&);
    virtual ~Tower() = default;

    //auto& getTarget() { return target; }
    void setProjSpawnCb(ProjSpawnFunc callback);
    virtual Tower* clone() const override = 0;
    virtual void attack();
    virtual bool lookForTarget(std::vector<Seal*> const& enemies);
    virtual void update(float dt) override;

protected:
    Seal* target = nullptr;
    ProjSpawnFunc spawnProjectile;
    float attackTimerSec = 0.0f;

    void advanceAnimationFrame() override;
};

}