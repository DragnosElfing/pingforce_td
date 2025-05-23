#pragma once

#include "all.hpp"

namespace pftd {
namespace utils {
namespace parser {

struct ParseError : std::runtime_error
{
    using std::runtime_error::runtime_error;
};

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
        if (sourceStream.fail() || sourceStream.bad()) {
            throw ParseError{"(" + validLabel + ") Nem sikerült beolvasni a következő tokent!"};
        }

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
    /**
    * @brief
    *
    * @param sourceFile A fájlnak az elérési útvonala, ahonnan a konfigot betöltjük.
    */
    LevelConfigParser(std::string const& sourceFile);
    ~LevelConfigParser() = default;

    void parse() override;

    /**
    * @brief Mentett attribútum értékének kiolvasása.
    *
    * @param name Az attribútum neve.
    * @return Az attribútum értéke (mindig egy array).
    */
    std::vector<Vec2f> getAttribute(std::string name) const;

private:
    /*! Mentett [attribútum, érték] párok. */
    std::unordered_map<std::string, std::vector<Vec2f>> m_attribs;

    /**
    * @brief Következő attribútum beolvasása a konfigfájlból.
    *
    * @return A kapott attribútum neve.
    */
    std::string _getAttribute();

};

/*! Mentett játékállás betöltésére szolgál. */
class SaveFileParser final : public Parser
{
public:
    /*! Mentett játék betöltéséhez használt statisztika osztály. */
    struct StatsInfo
    {
        unsigned int score, wealth;
        int maxHp, hp;
    };

    /*! Mentett játék betöltéséhez használt entitás típusok. */
    enum class EntityType
    {
        TOWER = 0U,
        SEAL,
        PROJECTILE
    };

    /*! Mentett játék betöltéséhez használt entitás infó. */
    struct EntityInfo
    {
        /*! Típusa. */
        EntityType entityType;

        /*! Pozíciója. */
        utils::Vec2f position;

        /*! Típustól függő egyéb adat. */
        //union {
            /*! Ellenfél típusra valló adatok. */
            struct {
                unsigned int sealID;
                float lerpParam;
                bool goingBackwards;
                unsigned int hp;
            } seal;

            /*! Lövedék típusra valló adatok. */
            struct {
                unsigned int projID;
                utils::Vec2f direction;
                float speed;
            } proj;

            /*! Torony típusra valló adatok. */
            unsigned int towerID;
        //};
    };

//public:
    SaveFileParser(std::string const& sourceFile);
    ~SaveFileParser() = default;

    void parse() override;

    /**
    * @brief Mentett statisztika beolvasása: pont, pénz, HP.
    *
    * @return A mentett statisztikát tartalmazó struktúra.
    */
    StatsInfo const& getStats() const { return m_readStats; };

    /**
    * @brief Mentett entitások beolvasása.
    *
    * @return Ezeket az entitásokat (azoknak a lényeges információját) tartalmazó lista.
    */
    std::vector<EntityInfo> const& getEntities() const { return m_entities; };

private:
    /*! A beolvasott statisztika. */
    StatsInfo m_readStats;

    /*! A beolvasott entitás infók. */
    std::vector<EntityInfo> m_entities;

    /**
    * @brief Statisztika beolvasása a fájlból.
    */
    void _getStats();

    /**
    * @brief Következ entitás beolvasása a fájlból.
    */
    void _getEntity();
};

}
}
}
