#pragma once

#include "all.hpp"

#if not defined(_PFTD_TEST) && not defined(CPORTA)
#include "SFML/Window/Event.hpp"
#endif

#include "objects/object_base.hpp"

namespace pftd {

#if not defined(_PFTD_TEST) && not defined(CPORTA)
/*! Nézet ősosztály. */
class Scene 
{
    using ObjPtrVec = std::vector<Object*>;
public:
    Scene() = default;

    Scene(Scene const&) = delete;
    Scene(Scene&&) noexcept = delete;
    
    /**
    * @brief Törli a kezelt objektumokat.
    */
    virtual ~Scene();

    /**
    * @brief `objects` getter (konstans).
    *
    * @return A kezelt elemek listája.
    */
    ObjPtrVec const& getObjects() const { return objects; }

    /**
    * @brief `objects` getter.
    *
    * @return A kezelt elemek listája.
    */
    ObjPtrVec& getObjects() { return objects; }

    /**
    * @brief `objects` getter.
    *
    * @param source A hangfájl elérési útvonala.
    * @param volume A zene hangereje.
    */
    void setMusic(std::string const& source, float volume = 100.0f);

    /**
    * @brief Nézet aktiválása/deaktiválása.
    *
    * @param active Aktiválás e?
    * @return Történt e állapot változás.
    */
    virtual bool toggleActive(bool active);

    /**
    * @brief Delegált események kezelése.
    *
    * @param event Kezelni kívánt esemény.
    */
    virtual void onEvent(sf::Event const& event) = 0;

    /**
    * @brief Update.
    *
    * @param dt Delta idő.
    */
    virtual void update(float dt) = 0;
    
protected:
    /*! Aktív e. */
    bool isActive = false;

    /*! Kezelt objektumok. */
    ObjPtrVec objects;

    /*! Háttérzene. */
    sf::Music* backgroundMusic = nullptr;
    
};
#endif

/*! Tesztelésre szánt nézet ősosztály. */
class MockScene 
{
    using ObjPtrVec = std::vector<MockObject*>;
public:
    MockScene() = default;

    MockScene(MockScene const&) = delete;
    MockScene(MockScene&&) noexcept = delete;
    
    virtual ~MockScene();

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
