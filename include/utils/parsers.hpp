#pragma once

#include "all.hpp"

namespace pftd 
{
namespace utils 
{
namespace parser 
{

template<typename StreamType = std::ifstream>
class Parser
{
public:
    Parser(StreamType const& sourceStream, std::string label = "");
    Parser(std::string const& sourceFile, std::string label = "");
    virtual ~Parser();

    void reset();
    bool isLabelValid(bool skip = true);
    void skip(size_t howMany, char until = '\n');
    void skip(char while_);
    template<typename T> T get()
    {
        this->_skipWhitespace();
        while(sourceStream.peek() == commentDenoter) {
            this->_skipLine();
            this->_skipWhitespace();
        }

        T got;
        sourceStream >> got;
        return got;
    }
    char peekAhead();
    virtual void parse() = 0;

protected:
    StreamType sourceStream;
    std::string validLabel;
    char commentDenoter = '#';

    //virtual bool validate() const = 0;

private:
    void _skipLine();
    void _skipWhitespace();

};

class LevelConfigParser final : public Parser<>
{
public:
    LevelConfigParser(std::string const& sourceFile);
    ~LevelConfigParser() = default;

    void parse() override;
    std::vector<std::pair<float, float>> getAttribute(std::string name) const;

private:
    std::string m_lastAttribute;
    std::unordered_map<std::string, std::vector<std::pair<float, float>>> m_attribs;

    std::string _getAttribute();

};

class SaveFileParser final : public Parser<>
{
    struct StatsInfo 
    {
        unsigned int score, wealth, hp;
    };

    //? Enzeknek biztos nem itt kéne lennie, de hová kerüljenek?
    enum class EntityType 
    {
        TOWER,
        SEAL,
        PROJECTILE
    };
    enum class TowerType
    {
        SNOWBALLER = 0,
        ICICLE_STABBER
    };
    enum class SealType
    {
        REGULAR = 0,
        CUB,
        ZOMBIE,
        FZC
    };

    struct EntityInfo 
    {
        EntityType entityType;
        union subtype {
            TowerType towerType;
            SealType sealType;
        };
        utils::Vec2f position;
        unsigned int sealHP;
    };

public:
    SaveFileParser(std::string const& sourceFile);
    ~SaveFileParser() = default;

    void parse() override;

    StatsInfo getStats() const;
    std::vector<EntityInfo> getEntities() const;

    //? De! Használhatjuk írásra is! Habár, ekkor már ez nem csak egy parser, hm?
    //? Esetleg egy új osztály, vagy csak más elnevezés?
    //? Talán?

private:
    StatsInfo m_readStats;
    std::vector<EntityInfo> m_entities;
};

}
}
}