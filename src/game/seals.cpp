#include "all.hpp"

#include "objects/entities/seals/fortified_zombie_cub.hpp"
#include "objects/entities/seals/regular.hpp"
#include "objects/entities/seals/cub.hpp"
#include "objects/entities/seals/seal_base.hpp"
#include "objects/entities/seals/zombie.hpp"

#ifndef _PFTD_DEBUG
    #define BANANACHANCE 0.01f
#else
    #define BANANACHANCE 0.1f
#endif

using namespace pftd;

/// Regular
RegularSeal::RegularSeal(FollowPath const& followpath):
    Seal{followpath, 
        // TODO: where Random static class?
    static_cast<float>(rand()) / static_cast<float>(RAND_MAX) <= BANANACHANCE ? "res/images/seals/banana.png" : "res/images/seals/reg.png", 
        {170, 170}, 2, 40.0f, 50}
{

}

Seal* RegularSeal::clone() const
{
    return new RegularSeal{followPath};
}
///

/// Cub
Cub::Cub(FollowPath const& followpath):
    Seal{followpath, "res/images/seals/cub.png", {130, 130}, 1, 65.0f, 50}
{

}

Seal* Cub::clone() const
{
    return new Cub{followPath};
}
///

/// Zombie
ZombieSeal::ZombieSeal(FollowPath const& followpath):
    Seal{followpath, "res/images/seals/zom.png", {170, 170}, 5, 10.0f, 100}
{

}

Seal* ZombieSeal::clone() const
{
    return new ZombieSeal{followPath};
}
///

/// FZC
FZC::FZC(FollowPath const& followpath):
    Seal{followpath, "res/images/seals/fzc.png", {130, 130}, 10, 15.0f, 200}
{

}

Seal* FZC::clone() const
{
    return new FZC{followPath};
}
///