#pragma once

#include <vector>

#include "SFML/Audio/Music.hpp"
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
    virtual ~Scene();

    std::vector<Object*> getObjects() const { return objects; }
    void setMusic(std::string const&);
    virtual bool setActive(bool);
    virtual void onEvent(sf::Event const&) = 0;
    virtual void update(float dt) = 0;
    
protected:
    bool isActive = false;
    std::vector<Object*> objects;
    sf::Music* backgroundMusic = nullptr;
};

}
