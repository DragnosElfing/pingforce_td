#include "mock_game/level.hpp"
#include "mock_objects/mock_entities/all_entities.hpp"
#include "utils/parsers.hpp"
#include "mock/app.hpp"
#include "mock/rman.hpp"

using namespace pftd_test;
using Stats = Level::Stats;
using Nest = Level::Nest;
using FP = FollowPath;

/// Stats
Stats::Stats(int maxHp, int currentHp, unsigned int score, unsigned int wealth):
    maxHp{maxHp}, hp{currentHp}, score{score}, money{wealth}
{

}

void Stats::serialize(std::ostream& out) const
{
    out << score << ' ' << money << ' ' << maxHp << ' ' << hp;
}
///

/// Nest
Nest::Nest(utils::Vec2f const& position):
    Entity{ResourceManager::getInstance()->getTexture("res/images/eggs.png"),
        {1024, 1024}, position, {2.0f*110, 2.0f*110}, 1}
{

}

Nest* Nest::clone() const
{
    return new Nest{position};
}
///

/// Level
Level::Level(std::string const& saveFile, std::string const& configFile):
    Object{{}, {}},

    config{configFile},
    saveFile{saveFile}
{
    config.parse();

    nest = new Nest{config.getAttribute("nestPosition")[0]};

    for(auto& [x, y] : config.getAttribute("followPath")) {
        followPath.append(new utils::Vec2{x, y});
    }
    followPath.append(new utils::Vec2{nest->getPosition()});
}

Level::~Level()
{
    if(selectedTower) delete selectedTower;
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

void Level::reset(Stats stats)
{
    this->stats = stats;
    // HP vesztés shenanigans.
    this->stats.hp = stats.maxHp;
    this->loseHP(stats.maxHp - stats.hp);

    this->deselectTower();

    // Kvázi destruktor.
    for(auto& tower : towers) {
        delete tower;
    }
    towers.clear();
    for(auto& seal : seals) {
        delete seal;
    }
    seals.clear();
    for(auto& proj : projectiles) {
        delete proj;
    }
    projectiles.clear();
}

void Level::loadFromSave()
{
    this->reset();

    utils::parser::SaveFileParser saveFileP {saveFile};
    try {
        saveFileP.parse();
    } catch(utils::parser::ParseError err) {
        print(err.what());
    }

    auto sInf = saveFileP.getStats();
    stats = Stats{sInf.maxHp, sInf.maxHp, sInf.score, sInf.wealth};
    this->loseHP(stats.maxHp - sInf.hp);

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

void Level::loseHP(int hpLost)
{
    if(hpLost >= stats.hp) {
        stats.hp = 0;
    } else {
        stats.hp -= hpLost;
    }

    nest->getSprite()->setSpriteRect({(stats.maxHp - stats.hp)*1024, 0}, {1024, 1024});
}

bool Level::placeTower()
{
    if(!selectedTower) return false;

    for(auto& tower : towers) {
        // Ha túl közel szeretnénk egymáshoz: ne.
        if(utils::Vec2f::distance(tower->getPosition(), selectedTower->getPosition())
            <= std::max(tower->properties.radiusPixel, selectedTower->properties.radiusPixel)) {
            return false;
        }
    }

    // Ha van elég pénzünk, akkor leteszi.
    if(stats.money >= selectedTower->properties.price) {
        stats.money -= selectedTower->properties.price;
        towers.push_back(selectedTower->clone());
        towers.back()->setProjSpawnCb([this](Projectile* projectile){
            projectiles.push_back(std::move(projectile));
        });
        this->deselectTower();

        return true;
    } else {
        return false;
    }

}

void Level::deselectTower()
{
    if(selectedTower) {
        delete selectedTower;
        selectedTower = nullptr;
    }
}

void Level::selectTower(Tower* newTower)
{
    this->deselectTower();
    selectedTower = newTower;
}

void Level::spawnSeal()
{
    Seal* newSeal = nullptr;

    float const r = 0.5; // Nem használunk véletlent tesztekben.
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

void Level::_spawnSeal(float dt)
{
    if(m_accuTimeSpawnSec >= 1.0f) {
        if(static_cast<float>(rand()) / static_cast<float>(RAND_MAX) <= 0.9f) {
            this->spawnSeal();
        }

        m_accuTimeSpawnSec = 0.0f;
    }

    m_accuTimeSpawnSec += dt;
}

void Level::_updateTowers(float dt)
{
    for(auto tower : towers) {
        tower->update(dt);
        tower->lookForTarget(seals);
    }
}

void Level::_updateSeals(float dt)
{
    for(auto it = seals.begin(); it != seals.end();) {
        auto& seal = *it;

        // Meghalt vagy befejezte az útját (igen, akkor is jár pont).
        if(seal->hp <= 0 || seal->hasCompletedPath()) {
            stats.money += seal->value;
            stats.score += seal->value * 3;

            delete seal;
            seal = nullptr;
            it = seals.erase(it);
        } else {
            // Tojáslopás.
            if(seal->isCurrentlyStealing) {
                this->loseHP();
                seal->isCurrentlyStealing = false;
            }

            seal->update(dt);

            it = std::next(it);
        }
    }
}

void Level::_updateProjectiles(float dt)
{
    for(auto it = projectiles.begin(); it != projectiles.end();) {
        auto& proj = *it;

        bool deletion = false;
        for(auto& seal : seals) {
            // Eltalált egy fókát.
            if(utils::Vec2f::distance(proj->getPosition(), seal->getPosition()) < 100) {
                seal->damage();

                delete proj;
                it = projectiles.erase(it);
                deletion = true;
                break;
            }
        }

        if(!deletion) {
            auto projPos = proj->getPosition();
            // Kijött a képernyőből.
            if(projPos.x <= 0 || projPos.y <= 0 || projPos.x >= App::getInstance()->getWindowWidth() || projPos.y >= App::getInstance()->getWindowHeight()) {
                    delete proj;
                    it = projectiles.erase(it);
                    deletion = true;
            }
        }

        if(!deletion) {
            it = std::next(it);
        }
    }

    for(auto& proj : projectiles) {
        proj->update(dt);
    }
}

void Level::update(float dt)
{
    this->_updateProjectiles(dt);
    this->_spawnSeal(dt);
    this->_updateSeals(dt);
    this->_updateTowers(dt);
}

void Level::save() const
{
    std::ofstream save_f {saveFile};
    if(!save_f.is_open()) {
        throw LoadError{"Nem lehetett megnyitni a mentés fájlt!"};
    }

    save_f << "pingforce\n";
    save_f << "\n# stats\n# Formátum: <pont> <pénz> <max. HP> <HP>\n";
    stats.serialize(save_f);

    save_f << "\n# entities\n# Formátum: <típus: \"seal\" | \"penguin\" | \"projectile\"> <ID: int> <pozíció: Vec2f> [ entitás típustól függő adatok... ]\n";
    for(auto const& tower : towers) {
        if(tower) {
            tower->serialize(save_f);
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

void Level::draw() const
{
    if(nest) nest->draw();
    for(auto& tower : towers) {
        tower->draw();
    }
    for(auto& seal : seals) {
        seal->draw();
    }
    for(auto& proj : projectiles) {
        proj->draw();
    }

    if(selectedTower) selectedTower->draw();
}

///
