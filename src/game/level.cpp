#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/Graphics/Texture.hpp"

#include "game/level.hpp"
#include "resources.hpp"
#include "utils/logger.hpp"
#include "utils/parsers.hpp"
#include "utils/substitute_types.hpp"

using namespace pftd;
using Stats = Level::Stats;
using Nest = Level::Nest;
using FP = FollowPath;

/// Stats
Stats::Stats()
{

}

Stats::Stats(int maxHp, int currentHp, unsigned int score, unsigned int wealth):
    MAX_HP{maxHp}, hp{currentHp}, score{score}, money{wealth}
{

}
///

/// Nest
Nest::Nest(sf::Texture const& texture, utils::Vec2f const& position):
    position{position}, 
    sprite{new gr::Sprite{texture, {{0, 0}, {1024, 1024}}, position, {2.0f*radius, 2.0f*radius}, 1}}
{

}

Nest::~Nest()
{
    delete sprite;
}
///

/// FollowPath
FP::FollowPath()
{

}
///

/// Level
Level::Level(Stats stats):
    Object{{}, {}},

    stats{stats},
    config{"res/data/level.conf"}
{
    config.parse();

    nest = new Nest{ResourceManager::getInstance()->getTexture("res/images/eggs.png"), 
        {config.getAttribute("nestPosition")[0].first, config.getAttribute("nestPosition")[0].second}};

    for(auto& [x, y] : config.getAttribute("followPath")) {
        followPath.append({x, y});
    }
}

Level::~Level()
{
    if(nest) delete nest;
    for(auto& tower : towers) {
        delete tower;
    }
    for(auto& seal : seals) {
        delete seal;
    }
}

void Level::loseHP(int hpLost)
{
    if(hpLost >= stats.hp) {
        stats.hp = 0U;
    } else {
        stats.hp -= hpLost;
    }

    nest->sprite->setSpriteRect({{(stats.MAX_HP - stats.hp)*1024, 0}, {1024, 1024}});
}

bool Level::placeTower()
{
    if(!selectedTower) return false;

    for(auto& tower : towers) {
        if(utils::Vec2f::distance(tower->getPosition(), selectedTower->getPosition()) 
            <= std::max(tower->radiusPixel, selectedTower->radiusPixel)) {
            return false;
        }
    }

    if(stats.money >= selectedTower->price) {
        stats.money -= selectedTower->price;
        towers.push_back(std::move(selectedTower));
        selectedTower = nullptr;
        
        return true;
    } else {
        return false;
    }

}

void Level::deselectTower()
{
    if(selectedTower != nullptr) {
        delete selectedTower;
        selectedTower = nullptr;
    }
}

void Level::selectTower(Tower* newTower)
{
    this->deselectTower();
    selectedTower = new Tower{*newTower};
}

void Level::spawnSeal()
{
    auto newSeal = new Seal{followPath};
    newSeal->setPosition(followPath.getContainer().at(5));
    seals.push_back(newSeal);
}

void Level::update(float dt)
{
    for(auto& entity : towers) {
        entity->update(dt);
    }
    for(auto& entity : seals) {
        entity->update(dt);
    }
}

bool Level::isGameOver() const 
{
    return stats.hp == 0U;
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(auto& tower : towers) {
        tower->draw(target, states);
    }
    for(auto& seal : seals) {
        seal->draw(target, states);
    }

    if(nest) nest->sprite->draw(target, states);
    if(selectedTower) selectedTower->draw(target, states);
}

///