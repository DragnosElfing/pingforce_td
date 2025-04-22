#pragma once

#include "all.hpp"

namespace pftd 
{
namespace utils 
{
namespace parser 
{

class Parser
{
public:
    /**
    * @brief
    *
    * @param sourceFile A fájlnak az elérési útvonala, ahonnan olvasni szeretnénk.
    * @param label A karaktersor, amellyel kötelezően kezdődnie kell a fájlnak.
    */
    Parser(std::string const& sourceFile, std::string label = "");
    
    virtual ~Parser();

    /**
    * @brief Reseteli az IO flageket, és a stream elejére mozgatja a kurzort.
    */
    void reset();

    /**
    * @brief Megmondja, hogy tényleg a megadott karaktersorral kezdődik e a stream.
    *
    * @param skip Ha beolvasta a karaktersort, akkor skippelje e, vagy visszamozogjon.
    * @return Helyes e a karaktersor.
    */
    bool isLabelValid(bool skip = true);

    /**
    * @brief Ugorjon át valamennyi karaktert, de legfeljebb egy megadottig.
    *
    * @param howMany Ennyi karaktert ugrik át legfeljebb.
    * @param until Eddig a karakterig ugrik át mindent, ha még nem ugrott át `howMany` számút (ezt is beleértve).
    */
    void skip(size_t howMany, char until = '\n');

    /**
    * @brief Ugorjon át mindent amíg a következő karakter egy megadott.
    *
    * @param while_ Addig ugor át mindent, amíg ez a következő karakter.
    */
    void skip(char while_);

    /**
    * @brief Beolvas egy megadott típusú adatot.
    *
    * Megjegyzés: a kommenteket átugorja.
    *
    * @return A beolvasott adat.
    */
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

    /**
    * @brief Megnézi, hogy milyen karakter van a kurzornál (lásd: megjegyzés).
    *
    * Megjegyzés: átugorja a white space-eket és a kommenteket, és csak az azutáni karaktert nézi meg.
    *
    * @return A kurzornál levő karakter.
    */
    char peekAhead();

    /**
    * @brief A parse főciklus.
    */
    virtual void parse() = 0;

protected:
    /*! Input stream. */
    std::ifstream sourceStream;

    /*! Elvárt karaktersor, amivel a streamnek kezdődnie kell. */
    std::string validLabel;

    /*! Kommentet jelölő karakter (ezt követően a sorban minden karakter a komment része). */
    char commentDenoter = '#';

    //virtual bool validate() const = 0;

private:
    /**
    * @brief Egész sor átugrása.
    */
    void _skipLine();

    /**
    * @brief Whitespace-ek átugrása.
    */
    void _skipWhitespace();

};

/*! 
    Egy szint alap beállításait tudjuk vele betölteni:
    az ellenfelek által követett útvonalat és a fészek helyzetét.
*/
class LevelConfigParser final : public Parser
{
public:
    LevelConfigParser(std::string const& sourceFile);
    ~LevelConfigParser() = default;

    void parse() override;
    std::vector<Vec2f> getAttribute(std::string name) const;

private:
    std::string m_lastAttribute;
    std::unordered_map<std::string, std::vector<Vec2f>> m_attribs;

    std::string _getAttribute();

};

/*! Mentett játékállás betöltésére szolgál. */
class SaveFileParser final : public Parser
{
    //? Ezeknek biztos nem itt kéne lennie.
    // struct StatsInfo 
    // {
    //     unsigned int score, wealth, hp;
    // };

    // enum class EntityType 
    // {
    //     TOWER,
    //     SEAL,
    //     PROJECTILE
    // };
    // enum class TowerType
    // {
    //     SNOWBALLER = 0,
    //     ICICLE_STABBER
    // };
    // enum class SealType
    // {
    //     REGULAR = 0,
    //     CUB,
    //     ZOMBIE,
    //     FZC
    // };

    // struct EntityInfo 
    // {
    //     EntityType entityType;
    //     union subtype {
    //         TowerType towerType;
    //         SealType sealType;
    //     };
    //     utils::Vec2f position;
    //     unsigned int sealHP;
    // };

public:
    SaveFileParser(std::string const& sourceFile);
    ~SaveFileParser() = default;

    void parse() override;

    // StatsInfo getStats() const;
    // std::vector<EntityInfo> getEntities() const;

private:
    // StatsInfo m_readStats;
    // std::vector<EntityInfo> m_entities;
};

}
}
}