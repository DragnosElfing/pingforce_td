
#include "SFML/Audio/Sound.hpp"

#include "resources.hpp"

namespace pftd 
{

class Level
{
public:
    // TODO: ctor
    struct Stats
    {
        unsigned int round = 0U;
        unsigned int money = 0U;
        int const MAX_HP = 3;
        int hp = MAX_HP;
    };

    struct Nest
    {
        int posX, posY;
        int const radius = 110;
        gui::Image sprite;

        explicit Nest(sf::Texture const& texture, int posX, int posY);
        Nest(Nest const& other) = default;
        ~Nest() = default;
    };

    struct FollowPath : public Object
    {
        struct PathEndPoint
        {
            float x, y;
        };

        float followerVelocity = 1.0f;
        std::vector<PathEndPoint> path;
        
        FollowPath(): Object({}, {}, 1000) {}

        void draw(sf::RenderTarget&, sf::RenderStates) const;
    };

    Nest nest;
    Stats stats;
    FollowPath followPath;
    
    // TODO: take in a Stats object
    Level(Nest const& nestConfig);
    virtual ~Level() = default;

    virtual void loseHP(int hpLost = 1);
    bool isGameOver() const;

private:

};

}
