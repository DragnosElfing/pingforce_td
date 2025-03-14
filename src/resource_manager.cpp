#include "resources.hpp"
#include "utils/logger.hpp"

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
    return defaultFont.openFromFile(path);
}

bool ResourceManager::addTextureToRepo(std::string const& source, std::string const& id)
{
    if(m_textures.find(id) != m_textures.end()) {
        return false;
    }
    
    m_textures[id] = sf::Texture{sf::Image{source}};

    return true;
}

sf::Texture const* ResourceManager::getTextureFromRepo(std::string const& id) const
{
    if(m_textures.find(id) != m_textures.end()) {
        return &m_textures.at(id);
    }

    return nullptr;
}