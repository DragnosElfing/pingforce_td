
#include "all.hpp"

#include "objects/entities/projectiles/projectile_base.hpp"
#include "objects/entities/seals/seal_base.hpp"
#include "objects/entities/towers/tower_base.hpp"
#include "objects/serializable.hpp"
#include "utils/parsers.hpp"

namespace pftd 
{

/*! Játéklogikát és entitásokat tartalmazó osztály. */
class Level : public Object
{
public:
    /*! Fészek. */
    struct Nest // TODO: should inherit from Object
    {
        utils::Vec2f position;
        int const radius = 110;
        gr::Sprite* sprite = nullptr;

        explicit Nest(sf::Texture const& texture, utils::Vec2f const& position);
        Nest(Nest const& other) = default;
        ~Nest();
    };

    /*! Játékállás / statisztika. */
    struct Stats : public Serializable
    {
        int const MAX_HP = 3;
        int hp = MAX_HP;
        unsigned int score = 0U;
        unsigned int money = 100U;

        explicit Stats();
        explicit Stats(int maxHp, int currentHp, unsigned int score, unsigned int wealth);
    };

    /*! Játékos statisztika. */
    Stats stats;

    /*! Lehelyezni kívánt torony. */
    Tower* selectedTower = nullptr;
    
    /**
    * @brief
    *
    * @param stats Kezdeti játékállás.
    */
    Level(Stats stats = Stats{});
    virtual ~Level();

    /**
    * @brief HP vesztés.
    *
    * @param hpLost Ennyi HP-t veszít a játékos. 
    */
    virtual void loseHP(int hpLost = 1);

    /**
    * @brief Kiválasztott torny lehelyezése.
    *
    * @return Sikerült e lehelyezni? 
    */
    virtual bool placeTower();

    /**
    * @brief Kiválasztott torony törlése. 
    */
    void deselectTower();

    /**
    * @brief Torony kiválasztása.
    *
    * Ezt a játék nézet "eszköztárja" adja át.
    *
    * @param newTower Lehelyezni kívánt torony.
    */
    void selectTower(Tower* newTower);

    /**
    * @brief Update.
    *
    * @param dt Delta idő.
    */
    void update(float dt);

    /**
    * @brief Vége van e játéknak?
    *
    * @return Vesztett e a játékos? 
    */
    bool isGameOver() const;

    /**
    * @brief Objektum megjelenítése.
    *
    * @param target Hol legyen megjelenítve? Ez általában egy ablak.
    * @param states Render-eléshez szükséges egyéb állapotok.
    */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
    /*! A fészek (cél). */
    Nest* nest = nullptr;

    /*! Ellenségek által követett útvonal. */
    FollowPath followPath;

    /*! Lehelyezett tornyok. */
    std::vector<Tower*> towers;

    /*! Élő ellenfelek. */
    std::vector<Seal*> seals;

    /*! Lövedékek. */
    std::vector<Projectile*> projectiles;

    /*! Inicializáláshoz szükséges konfiguráció. */
    utils::parser::LevelConfigParser config;

    /**
    * @brief Ellenfél spawnolás.
    */
    void spawnSeal();

private:
    /*! Előző spawn óta eltelt idő. */
    float m_accuTimeSpawnSec = 0.0f;

};

}
