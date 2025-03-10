#pragma once

#include <vector>

#include "SFML/Window/Event.hpp"

#include "objects/object_base.hpp"
#include "resources.hpp"

namespace pftd {

class Scene 
{
public:
    Scene() = default;
    Scene(Scene const&) = default;
    Scene(Scene&&) noexcept = default;
    virtual ~Scene() = default;

    std::vector<Object*> getObjects() const { return objects; }
    virtual void onEvent(sf::Event const&) = 0;
    
protected:
    std::vector<Object*> objects;
};

}
