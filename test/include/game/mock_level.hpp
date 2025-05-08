
#include "all.hpp"

#include "objects/entities/projectiles/mock_projectile_base.hpp"
#include "objects/entities/seals/mock_seal_base.hpp"
#include "objects/entities/towers/mock_tower_base.hpp"
#include "utils/serializable.hpp"
#include "utils/parsers.hpp"

namespace pftd_test
{

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

        ~Nest();
    };

    /*! Játékállás / statisztika teszteléshez. */
    struct Stats : public utils::Serializable
    {
        int const MAX_HP = 3;
        int hp = MAX_HP;
        unsigned int score = 0U;
        unsigned int money = 100U;

        explicit Stats();
        explicit Stats(int maxHp, int currentHp, unsigned int score, unsigned int wealth);

        void serialize(std::ostream& out) const override;
        ;
    };

    Stats stats;
    Tower* selectedTower = nullptr;
    
    Level(Stats stats = Stats{});
    virtual ~Level();

    virtual void loseHP(int hpLost = 1);
    virtual bool placeTower();
    void deselectTower();
    void selectTower(Tower* newTower);
    void update(float dt);
    bool isGameOver() const;
    virtual void draw() const override;

//protected:
    Nest* nest = nullptr;
    FollowPath followPath;
    std::vector<Tower*> towers;
    std::vector<Seal*> seals;
    std::vector<Projectile*> projectiles;
    utils::parser::LevelConfigParser config;

    void spawnSeal();

//private:
    float m_accuTimeSpawnSec = 0.0f;

};

}
