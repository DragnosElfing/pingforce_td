#ifndef CPORTA

#include "objects/gui/image.hpp"
#include "resources.hpp"

using namespace pftd::gr;

Sprite::Sprite(sf::Texture const& texture, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex):
    Object{position, size, zIndex},
    m_texture{texture},
    m_sprite{m_texture}
{
    m_sprite.setPosition({position.x, position.y});
    m_sprite.setScale({
        size.x / m_sprite.getLocalBounds().size.x,
        size.y / m_sprite.getLocalBounds().size.y
    });
}

Sprite::Sprite(std::string const& imageSrc, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex):
    Sprite{ResourceManager::getInstance()->getTexture(imageSrc), position, size, zIndex}
{

}

Sprite::Sprite(sf::Texture const& texture, sf::IntRect const& textureRect, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex):
    Object{position, size, zIndex},
    m_texture{texture},
    m_sprite{m_texture, textureRect}
{
    m_sprite.setPosition({position.x, position.y});
    m_sprite.setScale({
        this->size.x / m_sprite.getLocalBounds().size.x,
        this->size.y / m_sprite.getLocalBounds().size.y
    });
}

// Duplikáció elkerülése érdekében akár delegálni is lehetne egy másik konstruktornak ezt.
Sprite::Sprite(Sprite const& other):
    Object(other),
    m_texture{other.m_texture},
    m_sprite{other.m_sprite}
{
    m_sprite.setPosition({position.x, position.y});
    m_sprite.setScale({
        size.x / m_sprite.getLocalBounds().size.x,
        size.y / m_sprite.getLocalBounds().size.y
    });
}

Sprite::Sprite(Sprite&& other) noexcept:
    Object{std::move(other)},
    m_texture{other.m_texture},
    m_sprite{std::move(other.m_sprite)}
{
    m_sprite.setPosition({position.x, position.y});
    m_sprite.setScale({
        size.x / m_sprite.getLocalBounds().size.x,
        size.y / m_sprite.getLocalBounds().size.y
    });
}

void Sprite::scale(utils::Vec2f const& factor)
{
    m_sprite.setScale({m_sprite.getScale().x * factor.x, m_sprite.getScale().y * factor.y});
}

void Sprite::flipY()
{
    this->scale({-1.0f, 1.0f});
}

void Sprite::modColor(sf::Color const& color)
{
    m_sprite.setColor(color);
}

void Sprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}

void Sprite::setSpriteRect(sf::IntRect const& textureRect)
{
    m_sprite.setTextureRect(textureRect);
}

#endif
