#ifndef CPORTA

#include "resources.hpp"

using namespace pftd;

ResourceManager* ResourceManager::m_instance = nullptr;
ResourceManager* ResourceManager::create()
{
    if(m_instance != nullptr) {
        delete m_instance;
    }

    m_instance = new ResourceManager{};
    return m_instance;
}

void ResourceManager::loadDefaultFont(std::string const& path)
{
    // Az SFML nem várja el, hogy az előző font "be legyen zárva", úgyhogy simán felül lehet írni.
    if(!m_defaultFont.openFromFile(path)) {
        throw LoadError{"Nem lehetett megnyitni a betűtípust: " + path + '.'};
    }
}

sf::Texture const& ResourceManager::getTexture(std::string const& source)
{
    if(m_textures.find(source) != m_textures.end()) {
        return m_textures.at(source);
    }

    try {
        m_textures[source] = sf::Texture{sf::Image{source}};
    } catch(sf::Exception& sfError) {
        throw LoadError{"Nem sikerült betölteni a `" + source + "` képfájlt.\nSFML: " + sfError.what()};
    }
    return m_textures.at(source);
}

sf::SoundBuffer const& ResourceManager::getSound(std::string const& source)
{
    if(m_sounds.find(source) != m_sounds.end()) {
        return m_sounds.at(source);
    }

    try {
        m_sounds[source] = sf::SoundBuffer{source};
    } catch(sf::Exception sfError) {
        throw LoadError{"Nem sikerült betölteni a `" + source + "` hangfájlt.\nSFML: " + sfError.what()};
    }
    return m_sounds.at(source);
}

#endif
