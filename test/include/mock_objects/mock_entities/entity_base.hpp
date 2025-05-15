#pragma once

#include "all.hpp"

#include "mock_objects/mock_gui/image.hpp"
#include "mock_objects/object_base.hpp"
#include "utils/serializable.hpp"

namespace pftd_test
{

using namespace pftd;

/*! Tesztelésre szánt "actor" ősosztály: tornyok, fólák és lövedékek. */
class Entity : public Object
{
public:
    bool isAnimated = true;

    Entity(int texture, utils::Vec2i spriteSize, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex);
    Entity(std::string const& spriteSheetSrc, utils::Vec2i spriteSize, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex = 0);
    Entity(std::string const& spriteSrc, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex = 0);
    Entity(Entity const& other);
    virtual ~Entity();

    virtual Entity* clone() const = 0;
    virtual void update(float dt);
    virtual void draw() const override;
    void setPosition(utils::Vec2f position);
    auto getPosition() const { return position; }
    gr::Sprite const* getSprite() const { return currentSprite; }
    gr::Sprite* getSprite() { return currentSprite; }
    auto& getSpriteSheet() const { return spriteSheet; }
    void resetAnimation();

//protected:
    int spriteSheet;
    utils::Vec2i cellSize;
    size_t const CELL_N;
    size_t currentCell = 0U;
    gr::Sprite* currentSprite = nullptr;
    float frameDurationSec = 1.0f;
    float totalElapsedSec = 0.0f;

    virtual void advanceAnimationFrame();

};

}