#include "mock_objects/mock_gui/image.hpp"
#include "mock/rman.hpp"

using namespace pftd_test::gr;

Sprite::Sprite(int, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex):
    Object{position, size, zIndex}
{

}

Sprite::Sprite(std::string const& imageSrc, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex):
    Sprite{ResourceManager::getInstance()->getTexture(imageSrc), position, size, zIndex}
{

}

// Duplikáció elkerülése érdekében akár delegálni is lehetne egy másik konstruktornak ezt.
Sprite::Sprite(Sprite const& other):
    Object(other)
{

}

Sprite::Sprite(Sprite&& other) noexcept:
    Object{std::move(other)}
{

}

void Sprite::scale(utils::Vec2f const&)
{
    where();
}

void Sprite::modColor(uint32_t)
{
    where();
}

void Sprite::draw() const
{
    where();
}
