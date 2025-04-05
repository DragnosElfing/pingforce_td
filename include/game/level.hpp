
#include "SFML/Audio/Sound.hpp"

#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "objects/entities/seals/seal_base.hpp"
#include "objects/entities/towers/snowballer.hpp"
#include "objects/entities/towers/tower_base.hpp"
#include "objects/serializable.hpp"
#include "utils/parsers.hpp"
#include "utils/substitute_types.hpp"
#include "resources.hpp"
#include "objects/entities/seals/followpath.hpp"

namespace pftd 
{

class Level : public Object
{
public:
    struct Nest
    {
        utils::Vec2f position;
        int const radius = 110;
        gr::Sprite* sprite = nullptr;

        explicit Nest(sf::Texture const& texture, utils::Vec2f const& position);
        Nest(Nest const& other) = default;
        ~Nest();
    };

    struct Stats : public Serializable
    {
        int const MAX_HP = 3;
        int hp = MAX_HP;
        unsigned int score = 0U;
        unsigned int money = 100U;

        explicit Stats();
        explicit Stats(int maxHp, int currentHp, unsigned int score, unsigned int wealth);
    };

    Nest* nest = nullptr;
    Stats stats;
    FollowPath followPath;
    std::vector<Tower*> towers;
    std::vector<Seal*> seals;
    Tower* selectedTower = nullptr;
    utils::parser::LevelConfigParser config;
    
    Level(Stats stats = Stats{});
    virtual ~Level();

    virtual void loseHP(int hpLost = 1);
    virtual bool placeTower();
    void deselectTower();
    void selectTower(Tower* newTower);
    void spawnSeal();
    void update(float dt);
    bool isGameOver() const;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

}
