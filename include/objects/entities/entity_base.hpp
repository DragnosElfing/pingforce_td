#pragma once

#include <functional>
#include <optional>

#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "objects/gui/image.hpp"
#include "objects/object_base.hpp"
#include "objects/serializable.hpp"
#include "utils/substitute_types.hpp"

namespace pftd {
    
class Entity : public Object, public Serializable
{
    using OptSpriteRefConst = std::optional<std::reference_wrapper<gr::Sprite const>>;
    using OptSpriteRef = std::optional<std::reference_wrapper<gr::Sprite>>;
public:
    bool isAnimated = true;

    Entity(std::string const& spriteSheetSrc, utils::Vec2i spriteSize, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex = 0);
    Entity(sf::Texture const& texture, utils::Vec2i spriteSize, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex = 0);
    Entity(std::string const& spriteSrc, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex = 0);
    Entity(Entity const& other);
    virtual ~Entity();

    virtual void update(float dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void setPosition(utils::Vec2f position);
    auto getPosition() const { return position; }
    OptSpriteRefConst getSprite() const { if(currentSprite) return *currentSprite; else return {}; }
    OptSpriteRef getSprite() { if(currentSprite) return *currentSprite; else return {}; }

protected:
    // Feltételezzük, hogy egy sorban vannak a sprite-ok
    sf::Texture const& spriteSheet;
    utils::Vec2i cellSize;
    size_t const CELL_N;
    size_t currentCell = 0U;
    gr::Sprite* currentSprite = nullptr;
    float frameDurationSec = 1.0f;
    // Animációhoz van használva elsősorban
    float totalElapsedSec = 0.0f;

    virtual void advanceAnimationFrame();

};

}