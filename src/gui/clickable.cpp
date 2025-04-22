#include "objects/clickable.hpp"

using namespace pftd;

Clickable::Clickable(bool active): 
    isActive{active}
{

}

Clickable::Clickable(utils::Vec2f const& position, utils::Vec2f const& size, int zIndex, bool active):
    Object{position, size, zIndex},
    isActive{active}
{

}

void Clickable::setCallback(std::function<void()> callback)
{
    m_callback = callback;
}

void Clickable::handleClick(utils::Vec2i const& clickCoords)
{
    auto& xF = clickCoords.x;
    auto& yF = clickCoords.y;

    // A tesztek miatt direkt nem az `sf::Rect::contains` van használva
    bool contains = (position.x <= xF && xF <= position.x + size.x) && (position.y <= yF && yF <= position.y + size.y);
    if(contains) {
        this->m_callback();
    }
}