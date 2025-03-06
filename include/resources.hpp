#pragma once

#include "SFML/Graphics/Font.hpp"

namespace pftd {

class ResourceManager 
{
public:
    sf::Font defaultFont;

    ResourceManager() = default;
    ResourceManager(ResourceManager const&) = default;
    ResourceManager(ResourceManager&&) = default;
    ~ResourceManager();

    [[maybe_unused]]
    bool loadDefaultFont(std::string const&);
};

}
