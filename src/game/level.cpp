#include "game/level.hpp"
// TODO: put these inside a single header file
#include "objects/entities/entity_base.hpp"
#include "objects/entities/projectiles/projectile_base.hpp"
#include "objects/entities/projectiles/snowball.hpp"
#include "objects/entities/seals/cub.hpp"
#include "objects/entities/seals/fortified_zombie_cub.hpp"
#include "objects/entities/seals/regular.hpp"
#include "objects/entities/seals/zombie.hpp"
#include "objects/entities/towers/iciclestabber.hpp"
#include "objects/entities/towers/snowballer.hpp"
#include "utils/parsers.hpp"
#include "utils/random_gen.hpp"
#include "app.hpp"
#include "resources.hpp"

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

void Stats::serialize(std::ostream& out) const
{
    out << score << " " << money << " " << hp;
}
///

/// Nest
Nest::Nest(utils::Vec2f const& position):
    Entity{ResourceManager::getInstance()->getTexture("res/images/eggs.png"), 
        {1024, 1024}, position, {2.0f*110, 2.0f*110}, 1}
{

}

Nest::~Nest()
{
    
}

Nest* Nest::clone() const
{
    return new Nest{position};
}
///

/// FollowPath
FP::FollowPath()
{

}
///

/// Level
Level::Level(std::string const& saveFile, Stats stats):
    Object{{}, {}},

    stats{stats},
    config{"res/data/level.conf"},
    saveFile{saveFile}
{
    config.parse();

    nest = new Nest{config.getAttribute("nestPosition")[0]};

    for(auto& [x, y] : config.getAttribute("followPath")) {
        followPath.append(new utils::Vec2{x, y});
    }
    followPath.append(new utils::Vec2{nest->getPosition()});
}

Level::Level(std::string const& saveFile):
    Object{{}, {}},

    config{"res/data/level.conf"},
    saveFile{saveFile}
{
    // Először a konfig.
    config.parse();
    nest = new Nest{config.getAttribute("nestPosition")[0]};
    for(auto& [x, y] : config.getAttribute("followPath")) {
        followPath.append(new utils::Vec2{x, y});
    }

    // Utánna a mentett állás.
    utils::parser::SaveFileParser saveFileP {saveFile};
    try {
        saveFileP.parse();
    } catch(utils::parser::ParseError err) {
        print(err.what());
    }

    auto sInf = saveFileP.getStats();
    stats.hp = stats.MAX_HP;
    this->loseHP(stats.hp - sInf.hp);
    stats.money = sInf.wealth;
    stats.score = sInf.score;

    for(auto const& eInf : saveFileP.getEntities()) {
        switch(eInf.entityType) {
        case utils::parser::SaveFileParser::EntityType::TOWER:
            switch(eInf.towerID) {
            case static_cast<int>(TowerID::SNOWBALLER):
                towers.push_back(new Snowballer{eInf.position});
                break;
            case static_cast<int>(TowerID::ICICLE_STABBER):
                towers.push_back(new IcicleStabber{eInf.position});
                break;
            default: break; 
            }

            towers.back()->setProjSpawnCb([this](Projectile* projectile){
                projectiles.push_back(std::move(projectile));
            });

            break;
        case utils::parser::SaveFileParser::EntityType::SEAL:
            switch(eInf.seal.sealID) {
            case static_cast<int>(SealID::REGULAR):
                seals.push_back(new RegularSeal{followPath});
                break;
            case static_cast<int>(SealID::ZOMBIE):
                seals.push_back(new ZombieSeal{followPath});
                break;
            case static_cast<int>(SealID::CUB):
                seals.push_back(new Cub{followPath});
                break;
            case static_cast<int>(SealID::FZC):
                seals.push_back(new FZC{followPath});
                break;
            default: break;
            }

            seals.back()->setLerpState(eInf.seal.lerpParam, eInf.seal.goingBackwards);

            break;
        case utils::parser::SaveFileParser::EntityType::PROJECTILE:
            switch(eInf.proj.projID) {
            case static_cast<int>(ProjectileID::SNOWBALL):
                projectiles.push_back(new Snowball{eInf.position, eInf.proj.direction, eInf.proj.speed});
                break;
            default: break; 
            }

            break;
        default: break;
        }
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

    nest->getSprite()->setSpriteRect({{(stats.MAX_HP - stats.hp)*1024, 0}, {1024, 1024}});
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
        towers.push_back(selectedTower);
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
    selectedTower = newTower->clone();
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
    newSeal->setPosition(*followPath.getContainer().front());
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
            if(seal->isCurrentlyStealing) {
                this->loseHP();
                seal->isCurrentlyStealing = false;
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

    if(m_accuTimeSpawnSec >= 1.0f) {
        if(static_cast<float>(rand()) / static_cast<float>(RAND_MAX) <= 0.9f) {
            this->spawnSeal();
        }

        m_accuTimeSpawnSec = 0.0f;
    }

    m_accuTimeSpawnSec += dt;
}

bool Level::isGameOver() const 
{
    return stats.hp <= 0;
}

void Level::save() const
{
    std::ofstream save_f {saveFile};
    if(!save_f.is_open()) {
        throw std::runtime_error{"Nem lehetett megnyitni a mentés fájlt!"};
    }

    save_f << "pingforce\n";
    save_f << "\n# stats\n";
    stats.serialize(save_f);

    save_f << "\n# entities\n";
    for(auto const& tower : towers) {
        if(tower) {
            tower->serialize(save_f);
        } else {
            print("nullptr");
        }
    }
    for(auto const& seal : seals) {
        seal->serialize(save_f);
    }
    for(auto const& proj : projectiles) {
        proj->serialize(save_f);
    }

    save_f.close();
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(nest) nest->draw(target, states);
    for(auto& tower : towers) {
        tower->draw(target, states);
    }
    for(auto& seal : seals) {
        seal->draw(target, states);
    }
    for(auto& proj : projectiles) {
        proj->draw(target, states);
    }

    if(selectedTower) selectedTower->draw(target, states);
}

///