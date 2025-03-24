#include "objects/gui/image.hpp"

using namespace pftd::gui;

// TODO: no
Image::Image(Image&& other) noexcept:
    Image{
        std::move(other.m_texture), 
        std::move(other.m_sprite.getTextureRect()), 
        std::move(other.position), 
        std::move(other.size), 
        std::exchange(other.yIndex, 0)
    }
{ 

}

Image::Image(std::string const& imageSrc, sf::Vector2i const& position, sf::Vector2i const& size, int yIndex):
    Object{position, size, yIndex},
    m_texture{sf::Image{imageSrc}}, m_sprite{m_texture}
{
    m_sprite.setPosition(static_cast<sf::Vector2f>(this->position));
    m_sprite.setScale({
        this->size.x / m_sprite.getLocalBounds().size.x, 
        this->size.y / m_sprite.getLocalBounds().size.y
    });
}

Image::Image(sf::Texture const& texture, sf::Vector2i const& position, sf::Vector2i const& size, int yIndex):
    Object{position, size, yIndex},
    m_texture{texture}, m_sprite{m_texture}
{
    m_sprite.setPosition(static_cast<sf::Vector2f>(this->position));
    m_sprite.setScale({
        this->size.x / m_sprite.getLocalBounds().size.x, 
        this->size.y / m_sprite.getLocalBounds().size.y
    });
}

Image::Image(sf::Texture const& texture, sf::IntRect const& spriteRect, sf::Vector2i const& position, sf::Vector2i const& size, int yIndex):
    Object{position, size, yIndex},
    m_texture{texture}, m_sprite{m_texture, spriteRect}
{
    m_sprite.setPosition(static_cast<sf::Vector2f>(this->position));
    m_sprite.setScale({
        this->size.x / m_sprite.getLocalBounds().size.x, 
        this->size.y / m_sprite.getLocalBounds().size.y
    });
}

Image::Image(Image const& other):
    Image{
        other.m_texture,
        other.m_sprite.getTextureRect(),
        other.position,
        other.size,
        other.yIndex
    }
{ 
    
}


void Image::modColor(sf::Color const& color)
{
    m_sprite.setColor(color);
}

void Image::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}

void Image::setSpriteRect(sf::IntRect const& spriteRect)
{
    m_sprite.setTextureRect(spriteRect);
}