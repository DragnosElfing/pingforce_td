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

bool ResourceManager::loadDefaultFont(std::string const& path)
{
    return m_defaultFont.openFromFile(path);
}

sf::Texture const& ResourceManager::getTexture(std::string const& source)
{
    auto src = std::filesystem::path{std::filesystem::absolute(source)};

    if(m_textures.find(src) != m_textures.end()) {
        return m_textures.at(src);
    } else { // TODO: add error handling
        m_textures[src] = sf::Texture{sf::Image{src}};
        return m_textures[src];
    }
}

sf::SoundBuffer const& ResourceManager::getSound(std::string const& source)
{
    auto src = std::filesystem::path{std::filesystem::absolute(source)};

    if(m_sounds.find(src) != m_sounds.end()) {
        return m_sounds.at(src);
    } else { // TODO: add error handling
        m_sounds[src] = sf::SoundBuffer{src};
        return m_sounds[src];
    }
}