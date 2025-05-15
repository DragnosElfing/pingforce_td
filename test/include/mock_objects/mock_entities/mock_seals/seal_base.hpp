#pragma once

#include "mock_objects/mock_entities/entity_base.hpp"
#include "mock_objects/mock_entities/mock_seals/followpath.hpp"
#include "utils/substitute_types.hpp"

namespace pftd_test
{

using namespace pftd;

enum class SealID
{
    REGULAR = 0,
    CUB,
    ZOMBIE,
    FZC
};

/*! Fóka teszteléshez. */
class Seal : public Entity, public utils::Serializable
{
public:
    SealID id;
    bool isCurrentlyStealing = false;
    int hp;
    float speed;
    unsigned int value; 

    virtual ~Seal() = default;

    void lerpPath();
    virtual Seal* clone() const override = 0;
    void update(float dt) override;
    bool hasCompletedPath() const { return returned; }
    bool hasReachedNest() const { return reachedNest; }
    void damage(int hpLost = 1);
    void serialize(std::ostream& out) const override;
    void setLerpState(float param, bool backwards = false)
    {
        lerpParam = std::min(1.0f, std::max(param, 0.0f));
        reachedNest = backwards;
    }

//protected:
    Seal(FollowPath const& followPath, std::string const& spriteSrc, utils::Vec2f const& size, int hp, float speed, unsigned int value, int zIndex = 0);
    
    FollowPath const& followPath;
    
    // Interpolációhoz
    float lerpParam = 0.0f;
    bool reachedNest = false;
    bool returned = false;
    EndPoint nextPoint;

//private:
    void advanceAnimationFrame() override;

};

}