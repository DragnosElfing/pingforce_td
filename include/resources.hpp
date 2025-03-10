#pragma once

#include "SFML/Graphics/Font.hpp"
#include <unordered_map>

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
    // [[maybe_unused]]
    // bool addImageToRepo(std::string const&, std::string const&) const;
    // sf::Image const getImageFromRepo(std::string const&);

    [[nodiscard]]
    static ResourceManager* getInstance() { return m_instance; }
    [[maybe_unused]]
    static ResourceManager* create();
    static void destroy() { delete m_instance; }

private:
    ResourceManager() = default;

    //std::unordered_map<std::string, sf::Image> m_images;
    
    static ResourceManager* m_instance;
};

}
