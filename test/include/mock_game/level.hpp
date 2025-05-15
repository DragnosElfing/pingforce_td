
#include "all.hpp"

#include "mock_objects/mock_entities/mock_projectiles/projectile_base.hpp"
#include "mock_objects/mock_entities/mock_seals/seal_base.hpp"
#include "mock_objects/mock_entities/mock_towers/tower_base.hpp"
#include "mock_objects/mock_entities/mock_seals/followpath.hpp"
#include "utils/serializable.hpp"
#include "utils/parsers.hpp"

namespace pftd_test {

using namespace pftd;

/*! Játéklogikát és entitásokat tartalmazó osztály teszteléshez. */
class Level : public Object
{
public:
    /*! Fészek teszteléshez. */
    struct Nest : public Entity
    {
        int const radiusPixel = 110;

        explicit Nest(utils::Vec2f const& position);
        Nest(Nest const& other) = default;
        ~Nest() = default;

        Nest* clone() const override;

    };

    /*! Játékállás / statisztika teszteléshez. */
    struct Stats : public utils::Serializable
    {
        int maxHp = 3;
        int hp = maxHp;
        unsigned int score = 0U;
        unsigned int money = 100U;

        explicit Stats() = default;
        explicit Stats(int maxHp, int currentHp, unsigned int score, unsigned int wealth);

        void serialize(std::ostream& out) const override;
    };

    Stats stats;
    Tower* selectedTower = nullptr;
    
    Level(std::string const& saveFile, Stats stats);
    Level(std::string const& saveFile);
    virtual ~Level();

    virtual void loseHP(int hpLost = 1);
    virtual bool placeTower();
    void deselectTower();
    void selectTower(Tower* newTower);
    void update(float dt);
    bool isGameOver() const { return stats.hp <= 0; };
    virtual void draw() const override;
    void save() const;
    void reset(Stats stats);

//protected:
    Nest* nest = nullptr;
    FollowPath followPath;
    std::vector<Tower*> towers;
    std::vector<Seal*> seals;
    std::vector<Projectile*> projectiles;
    utils::parser::LevelConfigParser config;
    std::string saveFile;

    void spawnSeal();

//private:
    float m_accuTimeSpawnSec = 0.0f;

    void _spawnSeal(float dt);
    void _updateSeals(float dt);
    void _updateTowers(float dt);
    void _updateProjectiles(float dt);

};

}
