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
    where();
    return defaultFont.openFromFile(path);
}