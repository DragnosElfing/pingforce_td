#pragma once

#include "all.hpp"

#include "objects/object_base.hpp"
#include "utils/substitute_types.hpp"

namespace pftd
{

// TODO: create source file
/*! Kattintható (interaktálható) objektum. */
class Clickable : public Object
{
public:
    /*! Aktív e. */
    bool isActive;

    Clickable(bool active = true): 
        isActive{active}
    {}
    Clickable(utils::Vec2f const& position, utils::Vec2f const& size, int zIndex = 0, bool active = true):
        Object{position, size, zIndex},
        isActive{active}
    {}

    /**
    * @brief Callback beállítása.
    *
    * @param callback A kattintásra lefuttatni kívánt függvény.
    */
    virtual void setCallback(std::function<void()> callback)
    {
        m_callback = callback;
    }

    /**
    * @brief Kattintás kezelése.
    *
    * @param clickCoords Kurzor koordinátái kattintáskor.
    */
    virtual void handleClick(utils::Vec2i const& clickCoords)
    {
        auto& xF = clickCoords.x;
        auto& yF = clickCoords.y;

        // A tesztek miatt direkt nem az `sf::Rect::contains` van használva
        bool contains = (position.x <= xF && xF <= position.x + size.x) && (position.y <= yF && yF <= position.y + size.y);
        if(contains) {
            this->m_callback();
        }
    }

protected:
    /*! Callback: akkor fut le, ha az objektumra rákattintunk. */
    std::function<void()> m_callback;

};

};