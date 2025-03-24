#pragma once

#include <unordered_map>

#include "SFML/Audio/SoundBuffer.hpp"
#include "SFML/Graphics/Font.hpp"

#include "objects/gui/image.hpp"

namespace pftd {

class ResourceManager final
{
public:
    sf::Font defaultFont;

    ResourceManager(ResourceManager const&) = delete;
    ResourceManager(ResourceManager&&) = delete;
    ~ResourceManager();

    [[maybe_unused]]
    bool loadDefaultFont(std::string const&);
    sf::Texture const& getTexture(std::string const&);
    sf::SoundBuffer const& getSound(std::string const&);

    [[nodiscard]]
    static ResourceManager* getInstance() { return m_instance; }
    [[maybe_unused]]
    static ResourceManager* create();
    static void destroy() { delete m_instance; }

private:
    ResourceManager() = default;

    std::unordered_map<std::string, sf::Texture> m_textures;
    std::unordered_map<std::string, sf::SoundBuffer> m_sounds;
    
    static ResourceManager* m_instance;
};

}
