#include "mock/rman.hpp"

using namespace pftd_test;

ResourceManager* ResourceManager::m_instance = nullptr;
ResourceManager* ResourceManager::create()
{
    if(m_instance != nullptr) {
        delete m_instance;
    }

    m_instance = new ResourceManager{};
    return m_instance;
}

static bool isAvailable(std::string const& path)
{
    std::ifstream sourceF {path};
    bool isAvailable = sourceF.good();
    sourceF.close();

    return isAvailable;
}

bool ResourceManager::loadDefaultFont(std::string const& source)
{
    return isAvailable(source);
}

int ResourceManager::getTexture(std::string const& source)
{
    if(m_textures.find(source) != m_textures.end()) {
        return m_textures.at(source);
    }

    if(!isAvailable(source)) {
        throw LoadError{"Nem sikerült betölteni a `" + source + "` képfájlt."};
    }
    m_textures[source] = source.size();

    return m_textures.at(source);
}

int ResourceManager::getSound(std::string const& source)
{
    if(m_sounds.find(source) != m_sounds.end()) {
        return m_sounds.at(source);
    }

    if(!isAvailable(source)) {
        throw LoadError{"Nem sikerült betölteni a `" + source + "` hangfájlt."};
    }
    m_sounds[source] = source.size();

    return m_sounds.at(source);
}
