#include "SFML/Graphics/CircleShape.hpp"
#include "objects/entities/entity_base.hpp"
#include "objects/entities/towers/tower_base.hpp"
#include "objects/entities/seals/seal_base.hpp"
#include "resources.hpp"
#include "utils/logger.hpp"

using namespace pftd;

/// Entity

Entity::Entity(sf::Texture const& texture, utils::Vec2i spriteSize, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex):
    Object{position - size / 2, size, zIndex},
    spriteSheet{texture},
    cellSize{spriteSize},
    CELL_N{spriteSheet.getSize().x / cellSize.x},
    currentCell{0U},
    totalElapsedSec{0.0f}
{
    currentSprite = new gr::Sprite{
        spriteSheet, {{static_cast<int>(currentCell * cellSize.x), 0}, {cellSize.x, cellSize.y}},
        this->position, this->size, zIndex
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
    }
}

void Entity::setPosition(utils::Vec2f position)
{
    this->position = position;
    if(this->getSprite()) {
        auto const newPos = position - size / 2;
        this->getSprite()->get().m_sprite.setPosition(sf::Vector2f{newPos.x, newPos.y});
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
///

/// Tower
Tower::Tower(std::string const& spriteSheetSrc, utils::Vec2i spriteSize, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex):
    Entity{spriteSheetSrc, spriteSize, position, size, zIndex}
{
    frameDurationSec = attackSpeedSec / CELL_N;
}

Tower::Tower(std::string const& spriteSrc, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex):
    Tower{spriteSrc, {1024, 1024}, position, size, zIndex}
{

}

Tower::Tower(Tower const& other):
    Entity{other},
    attackSpeedSec{other.attackSpeedSec}
{
    frameDurationSec = attackSpeedSec / CELL_N;
}

void Tower::attack(bool instant)
{
    if(instant) return;
    // ...
}

Entity const* Tower::lookForTarget() const
{
    // ...
    return nullptr;
}
///

/// Seal

///