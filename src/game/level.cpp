#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/Graphics/Texture.hpp"

#include "game/level.hpp"
#include "utils/logger.hpp"

using namespace pftd;
using Nest = Level::Nest;
using FP = Level::FollowPath;

/// Nest
Nest::Nest(sf::Texture const& texture, int posX, int posY):
    posX{posX}, posY{posY}, 
    sprite{
        texture, 
        {{0, 0}, {1024, 1024}}, {posX, posY}, {2*radius, 2*radius}, 1
    }
{

}
///

/// FollowPath
void FP::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    #ifdef _PFTD_DEBUG
    
    if(path.size() <= 1) return;

    std::vector<sf::Vertex> linePrimitive;
    for(auto const& ep : path) {
        linePrimitive.push_back({{ep.x, ep.y}, sf::Color::Red});

        sf::CircleShape dot {5.0f};
        dot.setOrigin({5.0f, 5.0f});
        dot.setPosition({ep.x, ep.y});
        dot.setFillColor(sf::Color::Red);
        target.draw(dot, states);
    }
    target.draw(linePrimitive.data(), linePrimitive.size(), sf::PrimitiveType::LineStrip, states);

    #endif
}
///

/// Level
Level::Level(Nest const& nestConfig):
    nest{nestConfig}
{

}

void Level::loseHP(int hpLost)
{
    if(hpLost >= stats.hp) {
        stats.hp = 0U;
    } else {
        stats.hp -= hpLost;
    }

    nest.sprite.setSpriteRect({{(stats.MAX_HP - stats.hp)*1024, 0}, {1024, 1024}});
}

bool Level::isGameOver() const 
{
    return stats.hp == 0U;
}
///