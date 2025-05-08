#pragma once

#include "objects/entities/mock_entity_base.hpp"
#include "objects/entities/seals/mock_followpath.hpp"
#include "utils/substitute_types.hpp"

namespace pftd_test
{

using namespace pftd;

/*! Fóka teszteléshez. */
class Seal : public Entity
{
public:
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