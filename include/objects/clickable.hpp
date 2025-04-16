#pragma once

#include "all.hpp"

#include "objects/object_base.hpp"

namespace pftd
{

// TODO: create source file
class Clickable : public Object
{
public:
    bool isActive;

    Clickable(bool active = true): 
        isActive{active}
    {}
    Clickable(utils::Vec2f const& position, utils::Vec2f const& size, int zIndex = 0, bool active = true):
        Object{position, size, zIndex},
        isActive{active}
    {}

    virtual void setCallback(std::function<void()> callback)
    {
        m_callback = callback;
    }

    virtual void handleClick(int x, int y)
    {
        float xF = x;
        float yF = y;

        // A tesztek miatt direkt nem az `sf::Rect::contains` van használva
        bool contains = (position.x <= xF && xF <= position.x + size.x) && (position.y <= yF && yF <= position.y + size.y);
        if(contains) {
            this->m_callback();
        }
    }

protected:
    std::function<void()> m_callback;

};

};