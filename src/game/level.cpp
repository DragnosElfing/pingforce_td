#include "game/level.hpp"
// TODO: put these inside a single header file
#include "objects/entities/projectiles/projectile_base.hpp"
#include "objects/entities/projectiles/snowball.hpp"
#include "objects/entities/seals/cub.hpp"
#include "objects/entities/seals/fortified_zombie_cub.hpp"
#include "objects/entities/seals/regular.hpp"
#include "objects/entities/seals/zombie.hpp"
#include "utils/random_gen.hpp"
#include "app.hpp"

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
    for(auto& proj : projectiles) {
        delete proj;
    }
}

void Level::loseHP(int hpLost)
{
    if(hpLost >= stats.hp) {
        stats.hp = 0;
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
        towers.back()->setProjSpawnCb([this](Projectile* projectile){
            projectiles.push_back(std::move(projectile));
        });
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
    selectedTower = newTower; // TODO: clone method for entities
}

void Level::spawnSeal()
{
    Seal* newSeal = nullptr;

    std::uniform_real_distribution<float> dist {0.0, 1.0};
    float const r = utils::Random::generate(dist);
    if(r <= 0.4f) {
        newSeal = new RegularSeal{followPath};
    } else if(r <= 0.6f) {
        newSeal = new Cub{followPath};
    } else if(r <= 0.8f) {
        newSeal = new ZombieSeal{followPath};
    } else {
        newSeal = new FZC{followPath};
    }
    newSeal->setPosition(followPath.getContainer().front());
    seals.push_back(newSeal);
}

void Level::update(float dt)
{
    for(auto tower : towers) {
        tower->update(dt);
        tower->lookForTarget(seals);
    }

    for(auto& proj : projectiles) {
        proj->update(dt);
    }
    
    // Non-linear hozzáférés az elemekhez
    for(auto it = seals.begin(); it != seals.end();) {
        auto& seal = *it;
        
        if(seal->hp <= 0 || seal->hasCompletedPath()) {
            stats.money += seal->value;
            stats.score += seal->value * 3;
            delete seal;
            it = seals.erase(it);
        } else {
            if(seal->isStealing) {
                this->loseHP();
                seal->isStealing = false;
            }
            seal->update(dt);
            it = std::next(it);
        }
    }

    for(auto it = projectiles.begin(); it != projectiles.end();) {
        auto& proj = *it;

        bool deletion = false;
        for(auto& seal : seals) {
            if(utils::Vec2f::distance(proj->getPosition(), seal->getPosition()) < 100) {
                seal->damage();
                
                delete proj;
                it = projectiles.erase(it);
                deletion = true;
                break;
            }
        }

        if(!deletion) {
            auto projPos = sf::Vector2i{static_cast<int>(proj->getPosition().x), static_cast<int>(proj->getPosition().y)};
            if(!sf::IntRect{{0, 0}, {App::getInstance()->getWindowWidth(), App::getInstance()->getWindowHeight()}}
                .contains(projPos)) {
                    delete proj;
                    it = projectiles.erase(it);
                    deletion = true;
            }
        }

        if(!deletion) {
            it = std::next(it);
        }
    }

    if(accuTime >= 1.0f) {
        if(static_cast<float>(rand()) / static_cast<float>(RAND_MAX) <= 0.9f) {
            this->spawnSeal();
        }

        accuTime = 0.0f;
    }

    accuTime += dt;
}

bool Level::isGameOver() const 
{
    return stats.hp <= 0;
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(auto& tower : towers) {
        tower->draw(target, states);
    }
    for(auto& seal : seals) {
        seal->draw(target, states);
    }
    for(auto& proj : projectiles) {
        proj->draw(target, states);
    }

    if(nest) nest->sprite->draw(target, states);
    if(selectedTower) selectedTower->draw(target, states);
}

///