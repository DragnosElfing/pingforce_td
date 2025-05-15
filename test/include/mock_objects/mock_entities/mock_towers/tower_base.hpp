#pragma once

#include "mock_objects/mock_entities/entity_base.hpp"
#include "mock_objects/mock_entities/mock_projectiles/projectile_base.hpp"
#include "mock_objects/mock_entities/mock_seals/seal_base.hpp"

namespace pftd_test 
{

using namespace pftd;

enum class TowerID
{
    SNOWBALLER = 0,
    ICICLE_STABBER
};

/*! Torony (pingvin) teszteléshez. */
class Tower : public Entity, public utils::Serializable
{
    using ProjSpawnFunc = std::function<void(Projectile*)>;
public:
    struct TowerProperties
    {
        TowerID id;

        float radiusPixel = 120.0f;
        float attackRangePixel = 100.0f;
        float attackSpeedSec = 1.0f;
        unsigned int attackDamage = 1U;
        bool instantAttack = false;
        unsigned int price = 0U;

        TowerProperties(TowerID id, float radius = 120.0f, float attackRange = 100.0f, float attackSpeed = 1.0f,
            unsigned int attackDamage = 1U, bool instant = false, unsigned int price = 0U);

    } properties;

    Tower(TowerProperties const& props, std::string const& spriteSheetSrc, utils::Vec2i spriteSize, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex = 0);
    Tower(TowerProperties const& props, std::string const& spriteSrc, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex = 0);
    Tower(Tower const&);
    virtual ~Tower() = default;

    void setProjSpawnCb(ProjSpawnFunc callback);
    virtual Tower* clone() const override = 0;
    virtual void attack();
    virtual bool lookForTarget(std::vector<Seal*> const& enemies);
    virtual void update(float dt) override;
    void serialize(std::ostream& out) const override;

//protected:
    Seal* target = nullptr;
    ProjSpawnFunc spawnProjectile;
    float attackTimerSec = 0.0f;

    void advanceAnimationFrame() override;
};

}