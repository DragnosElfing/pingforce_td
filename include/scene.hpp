#pragma once

#ifndef CPORTA

#include "all.hpp"
#include "SFML/Window/Event.hpp"
#include "objects/object_base.hpp"

namespace pftd {

/*! Nézet ősosztály. */
class Scene
{
    using ObjPtrVec = std::vector<Object*>;
public:
    /*! Plusz információt közlő opciók. */
    enum class StateFlag : uint8_t
    {
        NONE = 0,
        LOAD_STATE = 1 << 0
    };

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
    * @brief Zene beállítása (loopon megy amíg aktív a nézet).
    *
    * @param source A hangfájl elérési útvonala.
    * @param volume A zene hangereje.
    */
    void setMusic(std::string const& source, float volume = 100.0f);

    /**
    * @brief Nézet aktiválása/deaktiválása: aktív -> nem aktív VAGY nem aktív -> aktív.
    *
    * @param flag Egyéb "kérést" közlő opció flag.
    */
    virtual void toggleActive(StateFlag flag = StateFlag::NONE);

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

}

#endif
