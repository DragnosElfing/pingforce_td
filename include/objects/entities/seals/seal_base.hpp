#pragma once

#include "objects/entities/entity_base.hpp"
#include "objects/entities/seals/followpath.hpp"
#include "utils/substitute_types.hpp"

namespace pftd 
{

class Seal : public Entity
{
public:
    virtual ~Seal() = default;

    void lerpPath();
    virtual Seal* clone() const override = 0;
    void update(float dt) override;
    bool hasCompletedPath() const { return returned; }
    bool hasReachedNest() const { return reachedNest; }
    void damage(int hpLost = 1);

    bool isStealing = false;
    int hp;
    float speed;
    unsigned int value; 
protected:
    Seal(FollowPath const& followPath, std::string const& spriteSrc, utils::Vec2f const& size, int hp, float speed, unsigned int value, int zIndex = 0);
    
    FollowPath const& followPath;
    // Interpolációhoz
    float lerpParam = 0.0f;
    bool reachedNest = false;
    bool returned = false;

private:
    void advanceAnimationFrame() override;

};

}