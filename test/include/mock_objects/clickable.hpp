#pragma once

#include "all.hpp"

#include "mock_objects/object_base.hpp"
#include "utils/substitute_types.hpp"

namespace pftd_test
{

using namespace pftd;

/*! Kattintható (interaktálható) objektum teszteléshez. */
class Clickable : public Object
{
public:
    bool isActive;

    Clickable(bool active = true);
    Clickable(utils::Vec2f const& position, utils::Vec2f const& size, int zIndex = 0, bool active = true);

    virtual void setCallback(std::function<void()> callback);
    virtual void handleClick(utils::Vec2i const& clickCoords);

//protected:
    std::function<void()> m_callback;

};

};