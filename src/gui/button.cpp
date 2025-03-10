#include "SFML/Graphics/RectangleShape.hpp"

#include "objects/gui/button.hpp"
#include "utils/logger.hpp"

using namespace pftd::gui;

//template<typename CallbackF>
Button::Button(sf::Text&& label, sf::FloatRect&& rect, bool active, int yIndex):
    isActive{active}, m_label{label}, m_rect{rect}
{
    where();

    this->yIndex = yIndex;
    // Középre igazítás
    m_label.setOrigin(m_label.getGlobalBounds().size / 2.0f + m_label.getLocalBounds().position);
    m_label.setPosition(m_rect.position + m_rect.size / 2.0f);
}

Button::~Button()
{
    where();
}

void Button::setCallback(std::function<void()> cb)
{
    m_callback = cb;
}

void Button::handleClick(sf::Vector2i const& interactionPos)
{
    if(m_rect.contains({static_cast<float>(interactionPos.x), static_cast<float>(interactionPos.y)})) {
        this->m_callback();
    }
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::RectangleShape rect;
    rect.setSize(m_rect.size);
    rect.setPosition(m_rect.position);
    rect.setFillColor(isActive ? sf::Color{100, 10, 100, 255} : sf::Color{100, 100, 100, 100});

    target.draw(rect, {});
    target.draw(m_label, states);
}