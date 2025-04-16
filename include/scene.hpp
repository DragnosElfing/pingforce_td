#pragma once

#include "all.hpp"

#include "SFML/Window/Event.hpp"

#include "objects/object_base.hpp"

namespace pftd {

class Scene 
{
    using ObjPtrVec = std::vector<Object*>;
    //using ObjPtrRefVec = std::vector<std::reference_wrapper<Object*>>;
public:
    Scene() = default;
    Scene(Scene const&) = delete;
    Scene(Scene&&) noexcept = delete;
    virtual ~Scene();

    ObjPtrVec const& getObjects() const { return objects; }
    ObjPtrVec& getObjects() { return objects; }
    void setMusic(std::string const& source, float volume = 100.0f);
    virtual bool setActive(bool active);
    virtual void onEvent(sf::Event const& event) = 0;
    virtual void update(float dt) = 0;
    
protected:
    bool isActive = false;
    ObjPtrVec objects;
    //ObjPtrRefVec objectsToRender;
    sf::Music* backgroundMusic = nullptr;
};

}
