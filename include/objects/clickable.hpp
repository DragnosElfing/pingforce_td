#pragma once

#include "all.hpp"

#include "objects/object_base.hpp"
#include "utils/substitute_types.hpp"

namespace pftd
{

/*! Kattintható (interaktálható) objektum. */
class Clickable : public Object
{
public:
    /*! Aktív e. */
    bool isActive;

    Clickable(bool active = true);
    Clickable(utils::Vec2f const& position, utils::Vec2f const& size, int zIndex = 0, bool active = true);

    /**
    * @brief Callback beállítása.
    *
    * @param callback A kattintásra lefuttatni kívánt függvény.
    */
    virtual void setCallback(std::function<void()> callback);

    /**
    * @brief Kattintás kezelése.
    *
    * @param clickCoords Kurzor koordinátái kattintáskor.
    */
    virtual void handleClick(utils::Vec2i const& clickCoords);

protected:
    /*! Callback: akkor fut le, ha az objektumra rákattintunk. */
    std::function<void()> m_callback;

};

};