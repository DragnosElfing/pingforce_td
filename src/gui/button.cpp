#ifndef CPORTA

#include "SFML/Graphics/RectangleShape.hpp"
#include "objects/gui/button.hpp"
#include "resources.hpp"

using namespace pftd::gr;

Button::Button(gr::Label const& label, utils::Vec2f const& position, utils::Vec2f const& size, bool active, int zIndex):
    Clickable{position, size, zIndex, active},

    label{label}, m_rect{{position.x, position.y}, {size.x, size.y}},
    m_clickSound{sf::Sound{ResourceManager::getInstance()->getSound("res/audio/buttonpress.mp3")}}
{
    // Középre igazítás
    this->label.getText().setOrigin(this->label.getText().getGlobalBounds().size / 2.0f + this->label.getText().getLocalBounds().position);
    this->label.getText().setPosition(m_rect.position + m_rect.size / 2.0f);

    m_clickSound.setVolume(20);
}

Button::~Button()
{
    if(m_background) delete m_background;
}

void Button::setSound(std::string const& source)
{
    m_clickSound.setBuffer(ResourceManager::getInstance()->getSound(source));
}

void Button::setBackground(std::string const& id)
{
    if(m_background) delete m_background;
    m_background = new Sprite{ResourceManager::getInstance()->getTexture(id),
        this->position, this->size, this->zIndex};
}

void Button::handleClick(utils::Vec2i const& clickCoords)
{
    m_clickSound.play();
    Clickable::handleClick(clickCoords);
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

    label.draw(target, states);
}

#endif
