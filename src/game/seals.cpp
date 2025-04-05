#include <cmath>
#include "objects/entities/seals/seal_base.hpp"
#include "utils/substitute_types.hpp"

using namespace pftd;

Seal::Seal(FollowPath const& followPath):
    Entity("res/images/eggs.png", {}, {170, 170}),
    followPath{followPath}
{

}

void Seal::lerpPath()
{
    // https://www.desmos.com/calculator/bd4zr21hx0

    auto& points = followPath.getContainer();
    if(points.size() <= 1) return;

    auto lerpProgress = lerpParam;
    float atLength = 0.0f;
    std::vector<float> totalLength {};
    for(size_t n = 0U; n < points.size() - 1; ++n) {
        atLength += utils::Vec2f::distance(points.at(n), points.at(n+1));
        print(atLength);
        float lengthSoFar = atLength;
        if(n > 0) {
            lengthSoFar += totalLength.at(n - 1);
        }
        totalLength.push_back(lengthSoFar);
    }
    lerpProgress *= atLength;

    size_t fromIdx = 0U;
    while(lerpProgress >= totalLength.at(fromIdx)) {
        ++fromIdx;
    }
    fromIdx = std::min(fromIdx, points.size() - 1);

    auto t = (lerpProgress - (fromIdx == 0 ? 0 : totalLength.at(fromIdx))) 
        / utils::Vec2f::distance(points.at(fromIdx+1), points.at(fromIdx));
    auto from = points.at(fromIdx);
    auto to = points.at(fromIdx + 1);

    this->setPosition(from*(1-t) + to*t);
    //print((lerpProgress - (fromIdx == 0 ? 0 : totalLength.at(fromIdx-1))) << " / " << utils::Vec2f::distance(points.at(fromIdx+1), points.at(fromIdx)));
}

void Seal::update(float dt)
{
    this->lerpPath();

    lerpParam += 10 * followPath.followerSpeed * dt / 1000.0f;
    if(lerpParam >= 1.0f) {
        lerpParam = 0.0f;
    }

    Entity::update(dt);
}

void Seal::advanceAnimationFrame()
{
    this->getSprite()->get().m_sprite.setScale({
        this->size.x / this->getSprite()->get().m_sprite.getLocalBounds().size.x, 
        this->size.y / this->getSprite()->get().m_sprite.getLocalBounds().size.y * (std::sin(totalElapsedSec)/8.0f + 1)
    });
}