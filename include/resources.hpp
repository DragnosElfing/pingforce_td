#pragma once

#include <unordered_map>

#include "SFML/Graphics/Font.hpp"

#include "objects/gui/image.hpp"

namespace pftd {

class ResourceManager 
{
public:
    sf::Font defaultFont;

    ResourceManager(ResourceManager const&) = delete;
    ResourceManager(ResourceManager&&) = delete;
    ~ResourceManager();

    [[maybe_unused]]
    bool loadDefaultFont(std::string const&);
    [[maybe_unused]]
    bool addTextureToRepo(std::string const&, std::string const&);
    sf::Texture const* getTextureFromRepo(std::string const&) const;

    [[nodiscard]]
    static ResourceManager* getInstance() { return m_instance; }
    [[maybe_unused]]
    static ResourceManager* create();
    static void destroy() { delete m_instance; }

private:
    ResourceManager() = default;

    std::unordered_map<std::string, sf::Texture> m_textures; // TODO: store absolute pathes instead of id's
    
    static ResourceManager* m_instance;
};

}
