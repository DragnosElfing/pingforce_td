#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "objects/gui/image.hpp"

namespace pftd 
{

/*! Az erőforrás-kezelő. */
class ResourceManager final
{
public:
    ResourceManager(ResourceManager const&) = delete;
    ResourceManager(ResourceManager&&) = delete;

    /**
    * @brief Felszabadítja a tárolt erőforrásokat.
    */
    ~ResourceManager();

    /**
    * @brief Az alapértelmezett (valójában csak ez van) betűtípus betöltése.
    *
    * Megjegyzés: `LoadError`-t dob, ha nem tudja betölteni bármi miatt is.
    *
    * @param path A betűtípus elérési útvonala.
    */
    void loadDefaultFont(std::string const& path);

    /**
    * @brief Új vagy tárolt textúra megszerzése.
    *
    * Megjegyzés: `LoadError`-t dob, ha nem találja.
    *
    * @param source A textúra elérési útvonala / azonosítója (megegyezik).
    * @return A kért textúra.
    */
    sf::Texture const& getTexture(std::string const& source);

    /**
    * @brief Új vagy tárolt audio buffer megszerzése.
    *
    * Megjegyzés: `LoadError`-t dob, ha nem találja.
    *
    * @param source A hangfájl elérési útvonala / azonosítója (megegyezik).
    * @return A kért audio buffer.
    */
    sf::SoundBuffer const& getSound(std::string const& source);

    /**
    * @brief `m_defaultFont` getter.
    *
    * @return Az alapértelmezett betűtípus.
    */
    sf::Font const& getDefaultFont() const { return m_defaultFont; }

    /**
    * @brief A singleton instance megszerzése.
    *
    * @return Az osztályhoz tartozó singleton instance.
    */
    static ResourceManager* getInstance() { return m_instance; }

    /**
    * @brief Létrehozza a singleton instance-t.
    *
    * Megjegyzés: Meg kell hívni a `destroy()`-t, ha már nincs szükség rá!
    *
    * @return Az osztályhoz tartozó singleton instance.
    */
    static ResourceManager* create();

    /**
    * @brief Törli a singleton instance-t.
    */
    static void destroy() { delete m_instance; }

private:
    // Az `m_instance` létrehozásához van használva.
    ResourceManager() = default;

    /*! A singleton instance. */
    static ResourceManager* m_instance;

    /*! Az alapértelmzett betűtípus. */
    sf::Font m_defaultFont;

    /*! Textúrák: [source, textúra példány] */
    std::unordered_map<std::string, sf::Texture> m_textures;

    /*! Audio: [source, hang buffer példány] */
    std::unordered_map<std::string, sf::SoundBuffer> m_sounds;
    
};

/*! Erőforrás-betöltés hiba. */
struct LoadError : public std::runtime_error
{
    using std::runtime_error::runtime_error;
};

}
