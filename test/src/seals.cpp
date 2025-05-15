#include "all.hpp"

#include "mock_objects/mock_entities/mock_seals/fzc.hpp"
#include "mock_objects/mock_entities/mock_seals/regular.hpp"
#include "mock_objects/mock_entities/mock_seals/cub.hpp"
#include "mock_objects/mock_entities/mock_seals/seal_base.hpp"
#include "mock_objects/mock_entities/mock_seals/zombie.hpp"
#include "utils/random_gen.hpp"

// Tesztekben nem használunk véletlent.
// #ifndef _PFTD_DEBUG
//     #define BANANACHANCE 0.01f
// #else
//     #define BANANACHANCE 0.1f
// #endif

using namespace pftd_test;

/// Regular
RegularSeal::RegularSeal(FollowPath const& followpath):
    Seal{followpath, "res/images/seals/reg.png", {170, 170}, 2, 40.0f, 50}
{
    id = SealID::REGULAR;
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
    id = SealID::CUB;
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
    id = SealID::ZOMBIE;
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
    id = SealID::FZC;
}

Seal* FZC::clone() const
{
    return new FZC{followPath};
}
///
