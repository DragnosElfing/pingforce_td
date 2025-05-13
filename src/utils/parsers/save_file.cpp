#include "utils/parsers.hpp"

using namespace pftd::utils::parser;

SaveFileParser::SaveFileParser(std::string const& sourceFile):
    Parser{sourceFile, "pingforce"}
{

}

void SaveFileParser::parse()
{
    if(!this->isLabelValid()) return;

    this->_getStats();
    while(true) {
        this->_getEntity();
        // Ha bármi miatt is ez nem sikerült, akkor be is fejezhettjük.
        // Ha ill-formed, akkor legyen az: legyen nehéz értelmezni az ebből adódó hibaüzenetet. >:)
        if(sourceStream.fail() || sourceStream.eof() || sourceStream.bad()) {
            break;
        }
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
    auto typeString = this->get<std::string>();
    if(sourceStream.eof()) return;

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
