#pragma once

#include "all.hpp"

namespace pftd_test {

/*! Az tesztelésre használt erőforrás-kezelő: funkcionalitása majdnem megegyezik a valódiéval, de valójában nem tárol konkrét erőforrásokat. */
class ResourceManager final
{
public:
    ResourceManager(ResourceManager const&) = delete;
    ResourceManager(ResourceManager&&) = delete;
    ~ResourceManager() = default;

    bool loadDefaultFont(std::string const& path);
    int getTexture(std::string const& source);
    int getSound(std::string const& source);
    int getDefaultFont() const { return 1; }

    static ResourceManager* getInstance() { return m_instance; }
    static ResourceManager* create();
    static void destroy() { delete m_instance; }

//private:
    ResourceManager() = default;

    static ResourceManager* m_instance;

    std::unordered_map<std::string, int> m_textures;
    std::unordered_map<std::string, int> m_sounds;

};

/*! Erőforrás-betöltés hiba. */
struct LoadError : public std::runtime_error
{
    using std::runtime_error::runtime_error;
};

}
