#include "resources.hpp"

using namespace pftd;

ResourceManager::~ResourceManager()
{

}

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
    //auto src = std::filesystem::path{std::filesystem::absolute(source)};

    if(m_textures.find(source) != m_textures.end()) {
        return m_textures.at(source);
    } else { // TODO: add error handling
        m_textures[source] = sf::Texture{sf::Image{source}};
        return m_textures[source];
    }
}

sf::SoundBuffer const& ResourceManager::getSound(std::string const& source)
{
    //auto src = std::filesystem::path{std::filesystem::absolute(source)};

    if(m_sounds.find(source) != m_sounds.end()) {
        return m_sounds.at(source);
    } else { // TODO: add error handling
        m_sounds[source] = sf::SoundBuffer{source};
        return m_sounds[source];
    }
}