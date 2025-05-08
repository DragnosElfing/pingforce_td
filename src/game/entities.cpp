#include "objects/entities/entity_base.hpp"
#include "objects/entities/projectiles/projectile_base.hpp"
#include "objects/entities/towers/tower_base.hpp"
#include "objects/entities/seals/seal_base.hpp"
#include "resources.hpp"

using namespace pftd;

/// Entity

Entity::Entity(sf::Texture const& texture, utils::Vec2i spriteSize, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex):
    Object{position, size, zIndex},
    spriteSheet{texture},
    cellSize{spriteSize},
    CELL_N{spriteSheet.getSize().x / cellSize.x},
    currentCell{0U},
    totalElapsedSec{0.0f}
{
    currentSprite = new gr::Sprite{
        spriteSheet, {{static_cast<int>(currentCell * cellSize.x), 0}, {cellSize.x, cellSize.y}},
        this->position - this->size / 2, this->size, zIndex
    };
}

Entity::Entity(std::string const& spriteSheetSrc, utils::Vec2i spriteSize, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex):
    Entity{ResourceManager::getInstance()->getTexture(spriteSheetSrc), spriteSize, position, size, zIndex}
{

}

// TODO: nem csak 1024x1024-es lehet
Entity::Entity(std::string const& spriteSrc, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex):
    Entity{spriteSrc, {1024, 1024}, position, size, zIndex}
{
    this->isAnimated = false;
}

Entity::Entity(Entity const& other):
    Entity{other.spriteSheet, other.cellSize, other.getPosition(), other.size, other.zIndex}
{

}

Entity::~Entity()
{
    if(currentSprite) delete currentSprite;
}

void Entity::update(float dt)
{
    totalElapsedSec += dt;
    this->advanceAnimationFrame();
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(currentSprite) {
        currentSprite->draw(target, states);
        sf::CircleShape circle {10.0f};
        circle.setFillColor(sf::Color::Red);
        circle.setPosition({position.x, position.y});
        target.draw(circle, states);
    }
}

void Entity::setPosition(utils::Vec2f position)
{
    this->position = position;
    if(this->getSprite()) {
        auto const newPos = position - size / 2;
        currentSprite->setPosition(newPos);
    }
}

void Entity::advanceAnimationFrame()
{
    if(!isAnimated) return;

    if(totalElapsedSec >= frameDurationSec) {
        totalElapsedSec = 0.0f;

        currentCell += 1;
        currentCell %= CELL_N;

        currentSprite->setSpriteRect({{static_cast<int>(currentCell * cellSize.x), 0}, {cellSize.x, cellSize.y}});
    }
}

void Entity::resetAnimation()
{
    if(!isAnimated) return;

    currentCell = 0U;
    totalElapsedSec = 0.0f;
    currentSprite->setSpriteRect({{0, 0}, {cellSize.x, cellSize.y}});
}
///

/// Tower
Tower::Tower(std::string const& spriteSheetSrc, utils::Vec2i spriteSize, float attackSpeedSec, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex):
    Entity{spriteSheetSrc, spriteSize, position, size, zIndex},

    attackSpeedSec{attackSpeedSec},
    spawnProjectile{[](Projectile*){}}
{
    frameDurationSec = attackSpeedSec / CELL_N;
}

Tower::Tower(std::string const& spriteSrc, float attackSpeedSec, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex):
    Tower{spriteSrc, {1024, 1024}, attackSpeedSec, position, size, zIndex}
{

}

Tower::Tower(Tower const& other):
    Entity{other},
    radiusPixel{other.radiusPixel},
    attackRangePixel{other.attackRangePixel},
    attackSpeedSec{other.attackSpeedSec},
    price{other.price},
    id{other.id}
{
    frameDurationSec = attackSpeedSec / CELL_N;
}

void Tower::setProjSpawnCb(ProjSpawnFunc callback)
{
    spawnProjectile = callback;
}

void Tower::attack()
{
    if(target) {
        if(instantAttack) target->damage();
        // else spawnProjectile(...)
    }
}

bool Tower::lookForTarget(std::vector<Seal*> const& enemies)
{
    // Shorthand.
    auto const inRange = [this](Seal* to) { 
        return utils::Vec2f::distance(to->getPosition(), this->getPosition()) < attackRangePixel; 
    };

    // Ha már van target, akkor nem keresünk újat.
    if(target && inRange(target)) {
        return true;
    }
    for(auto const& enemy : enemies) {
        if(inRange(enemy)) {
            target = enemy;
            return true;
        }
    }

    target = nullptr;
    attackTimerSec = 0.0f;
    Entity::resetAnimation();
    return false;

}

void Tower::update(float dt)
{
    Entity::update(dt);

    if(target) {
        if(attackTimerSec >= attackSpeedSec) {
            attackTimerSec = 0.0f;
            this->attack();
        }

        attackTimerSec += dt;
    }
}

void Tower::advanceAnimationFrame()
{
    if(target) {
        Entity::advanceAnimationFrame();
    }
}

void Tower::serialize(std::ostream& out) const
{
    out << "penguin " << static_cast<int>(id) << ' ' << position << '\n';
}
///

/// Seal
Seal::Seal(FollowPath const& followPath, std::string const& spriteSrc, utils::Vec2f const& size, int hp, float speed, unsigned int value, int zIndex):
    Entity(spriteSrc, {}, size, zIndex),
    
    hp{hp},
    speed{speed},
    value{value},
    followPath{followPath}
{

}

void Seal::lerpPath()
{
    // https://www.desmos.com/calculator/bd4zr21hx0 alapján (én készítettem)

    auto& points = followPath.getContainer();
    if(points.size() <= 1) return;

    auto lerpProgress = lerpParam;
    float atLength = 0.0f;
    std::vector<float> totalLength {};
    for(size_t n = 0U; n < points.size() - 1; ++n) {
        atLength += utils::Vec2f::distance(*points.at(n), *points.at(n+1));
        totalLength.push_back(atLength);
    }
    lerpProgress *= atLength;

    size_t fromIdx = 0U;
    while(lerpProgress > totalLength.at(fromIdx)) {
        ++fromIdx;
    }
    fromIdx = std::min(fromIdx, points.size() - 1);

    auto from = *points.at(fromIdx);
    auto to = *points.at(fromIdx + 1);
    auto t = (lerpProgress - (fromIdx != 0 ? totalLength.at(fromIdx - 1) : 0)) 
        / utils::Vec2f::distance(from, to);

    this->setPosition(from*(1-t) + to*t);

    nextPoint = to;
}

void Seal::damage(int hpLost)
{
    if(hp - hpLost < 0) {
        hp = 0;
    } else {
        hp -= hpLost;
    }

    if(hp > 0) {
        // Egyre pirosabbak, ahogy sebződnek.
        uint8_t newGB = std::max(255 - 155 / hp, 0);
        this->getSprite()->modColor({255, newGB, newGB, 255});
    }
}

void Seal::update(float dt)
{
    this->lerpPath();

    lerpParam += (reachedNest ? -1 : 1) * speed * dt / 1000.0f;
    if(lerpParam >= 1.0f) {
        lerpParam = 1.0f;
        reachedNest = true;
        isCurrentlyStealing = true;
    }

    if(lerpParam <= 0.0f && reachedNest) {
        returned = true;
    }

    // if((position - nextPoint).x < 0) {
    //     this->getSprite()->flipY();
    // }

    Entity::update(dt);
}

void Seal::advanceAnimationFrame()
{
    this->getSprite()->scale({1.0f, std::sin(2*totalElapsedSec*(speed / 10.0f))/50000.0f + 1.0f});
}

void Seal::serialize(std::ostream& out) const
{
    out << "seal " << static_cast<int>(id) << ' ' << position << ' ' << lerpParam << ' ' << reachedNest << ' ' << hp << '\n';
}
///

/// Projectile
Projectile::Projectile(std::string const& spriteSrc, utils::Vec2f const& position, 
    utils::Vec2f const& size, utils::Vec2f const& direction, float speed, float angularSpeed, int zIndex):
    Entity{spriteSrc, position, size, zIndex},

    direction{direction},
    linearSpeed{speed},
    angularVelocityRadPerSec{angularSpeed}
{

}

void Projectile::update(float dt)
{
    this->setPosition(this->getPosition() + direction * linearSpeed * dt);
}

void Projectile::serialize(std::ostream& out) const
{
    out << "projectile " << static_cast<int>(id) << ' ' << position << ' ' << direction << ' ' << linearSpeed << '\n';
}
///
