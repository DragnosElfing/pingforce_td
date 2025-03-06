#include "resources.hpp"
#include "utils/logger.hpp"

using namespace pftd;

ResourceManager::~ResourceManager()
{

}

bool ResourceManager::loadDefaultFont(std::string const& path)
{
    where();
    return defaultFont.openFromFile(path);
}