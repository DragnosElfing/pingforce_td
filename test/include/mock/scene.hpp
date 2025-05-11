#pragma once

#include "all.hpp"
#include "mock_objects/object_base.hpp"

namespace pftd_test 
{

/*! Tesztelésre szánt nézet ősosztály. */
class Scene 
{
    using ObjPtrVec = std::vector<Object*>;
public:
    Scene() = default;

    Scene(Scene const&) = delete;
    Scene(Scene&&) noexcept = delete;
    
    virtual ~Scene();

    ObjPtrVec const& getObjects() const { return objects; }
    ObjPtrVec& getObjects() { return objects; }
    void setMusic(std::string const& source, float volume = 100.0f);
    virtual bool toggleActive(bool active);
    virtual void onEvent(int event) = 0;
    virtual void update(float dt) = 0;
    
//protected:
    bool isActive = false;
    ObjPtrVec objects;
    
};

}
