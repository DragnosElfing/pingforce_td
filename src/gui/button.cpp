#include "SFML/Graphics/RectangleShape.hpp"

#include "objects/gui/button.hpp"
#include "resources.hpp"
#include "utils/logger.hpp"

using namespace pftd::gui;

//template<typename CallbackF>
Button::Button(sf::Text&& label, sf::FloatRect&& rect, bool active, int yIndex):
    Object{static_cast<sf::Vector2i>(rect.position), static_cast<sf::Vector2i>(rect.size)},
    isActive{active}, m_label{label}, m_rect{rect},
    m_clickSound{sf::Sound{ResourceManager::getInstance()->getSound("res/audio/buttonpress.mp3")}}
{
    this->yIndex = yIndex;
    
    // Középre igazítás
    m_label.setOrigin(m_label.getGlobalBounds().size / 2.0f + m_label.getLocalBounds().position);
    m_label.setPosition(m_rect.position + m_rect.size / 2.0f);

    m_clickSound.setVolume(20);
}

Button::~Button()
{
    if(m_background) delete m_background;
}

void Button::setCallback(std::function<void()> cb)
{
    m_callback = cb;
}

void Button::setSound(std::string const& source)
{
    m_clickSound.setBuffer(ResourceManager::getInstance()->getSound(source));
}

void Button::setBackground(std::string const& id)
{
    if(m_background) delete m_background;
    m_background = new Image{ResourceManager::getInstance()->getTexture(id), 
        this->position, this->size, this->yIndex};
}

void Button::handleClick(sf::Vector2i const& interactionPos)
{
    if(m_rect.contains({static_cast<float>(interactionPos.x), static_cast<float>(interactionPos.y)})) {
        m_clickSound.play();
        this->m_callback();
    }
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(m_background) {
        if(!isActive) {
            m_background->modColor(sf::Color{100, 100, 100, 100});
        }
        m_background->draw(target, states);
    } else {
        sf::RectangleShape rect;
        rect.setSize(m_rect.size);
        rect.setPosition(m_rect.position);
        rect.setFillColor(isActive ? sf::Color{100, 10, 100, 255} : sf::Color{100, 100, 100, 100});
        
        target.draw(rect, states);
    }
    
    target.draw(m_label, states);
}