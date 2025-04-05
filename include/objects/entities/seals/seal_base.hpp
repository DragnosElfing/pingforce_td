#pragma once

#include "objects/entities/entity_base.hpp"
#include "objects/entities/seals/followpath.hpp"

namespace pftd 
{

class Seal : public Entity
{
public:
    Seal(FollowPath const& followPath);
    virtual ~Seal() = default;

    void lerpPath();
    void update(float dt) override;

protected:
    FollowPath const& followPath;
    float lerpParam;

private:
    void advanceAnimationFrame() override;

};

}