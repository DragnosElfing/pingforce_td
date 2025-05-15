#include "utils/parsers.hpp"

using namespace pftd::utils::parser;

SaveFileParser::SaveFileParser(std::string const& sourceFile):
    Parser{sourceFile, "pingforce"}
{

}

void SaveFileParser::parse()
{
    if(!this->isLabelValid()) {
        throw ParseError{"Helytelen 'label'!"};
    }

    this->_getStats();
    while(!sourceStream.eof()) {
        this->_getEntity();

        // Hátha már a fájl végén vagyunk. Ekkor már a ciklusnak vége lesz.
        this->peekAhead();
    }
}

void SaveFileParser::_getStats()
{
    m_readStats.score = this->get<unsigned int>();
    m_readStats.wealth = this->get<unsigned int>();
    m_readStats.maxHp = this->get<int>();
    m_readStats.hp = this->get<int>();
}

void SaveFileParser::_getEntity()
{
    std::string typeString;
    try {
        typeString = this->get<std::string>();
    } catch(ParseError& parseError) {
        // Előfordulhat, hogy nincs is entitás mentve.
        return;
    }

    if(sourceStream.eof()) {
        throw ParseError{"Törzs nélküli entitás típus!"};
    }

    EntityType type;
    if(typeString == "penguin") {
        type = EntityType::TOWER;
    } else if(typeString == "seal") {
        type = EntityType::SEAL;
    } else if(typeString == "projectile") {
        type = EntityType::PROJECTILE;
    } else {
        throw ParseError{"Nincsen `" + typeString + "` entitás!"};
    }

    EntityInfo nextEntity;
    nextEntity.entityType = type;
    auto gotID = this->get<int>();
    switch(type) {
    case EntityType::TOWER:
        nextEntity.towerID = gotID;
        break;
    case EntityType::SEAL:
        nextEntity.seal.sealID = gotID;
        break;
    case EntityType::PROJECTILE:
        nextEntity.proj.projID = gotID;
        break;
    default: break;
    }
    nextEntity.position = this->get<utils::Vec2f>();
    switch(type) {
    case EntityType::SEAL:
        nextEntity.seal.lerpParam = this->get<float>();
        nextEntity.seal.goingBackwards = this->get<bool>();
        nextEntity.seal.hp = this->get<unsigned int>();
        break;
    case EntityType::PROJECTILE:
        nextEntity.proj.direction = this->get<utils::Vec2f>();
        nextEntity.proj.speed = this->get<float>();
        break;
    default: break;
    }

    m_entities.push_back(nextEntity);
}
