#include "gtest_lite.h"

// memtrace miatt :(
// egyelőre úgysincs szükség rá
#undef new
#undef delete

#include "utils/hetero_collection.hpp"
#include "utils/substitute_types.hpp"
#include "utils/parsers.hpp"


// #include "app.hpp"
// #include "scenes/game.hpp"
// #include "scenes/menu.hpp"

using namespace pftd;

int main()
{
    // A teszteléshez minden adattag & metódus publikus.

    // App::create(1440, 810, "TEST");
    // auto app = App::getInstance();

    // TEST(resource_checks, core)
    //     auto resMan = ResourceManager::getInstance();

    //     // Csak párat tesztelünk: mindenféle load helyesen működik e.
    //     // Létezik e a fájl amit beakarunk tölteni / már el van tárolva.
    //     EXPECT_TRUE(resMan->loadDefaultFont("res/fonts/Gorditas/Gorditas-Bold.ttf")) 
    //         << "Nem sikerült betölteni a betűtípust!\n";
    //     EXPECT_TRUE(resMan->getTexture("res/images/eggs.png"))
    //         << "Nem sikerült betölteni a tojások sprite-ját!";
    //     EXPECT_TRUE(resMan->getSound("res/audio/buttonpress.mp3"))
    //         << "Nem sikerült betölteni a gomb kattintás hangeffektet!";
        
    // END

    // TEST(scene_test, core)
    //     auto gameScene = new GameScene{};
    //     auto menuScene = new MenuScene{};
    //     app->addScene("game", gameScene, true);
    //     app->addScene("menu", menuScene);

    //     // Hamist kell visszaadnia, mert már aktív ez a nézet.
    //     EXPECT_FALSE(app->changeScene("game"));

    //     EXPECT_TRUE(app->changeScene("menu"));
    
    //     EXPECT_THROW(app->addScene("game", nullptr), SceneError)
    //         << "Nincs helyesen kezelve a nézet hozzáadás!";
    //     EXPECT_THROW(app->changeScene("nincsIlyen"), SceneError)
    //         << "Nincs helyesen kezelve a nézetváltás!";
    // END

    TEST(functionality, vec2)
        using namespace utils;

        Vec2i v1 {1, -2};
        Vec2i v2 {2, 2};

        EXPECT_EQ((Vec2{3, 0}), v1 + v2);
        EXPECT_EQ((Vec2{-1, -4}), v1 - v2);
        EXPECT_EQ((Vec2{3, -6}), v1 * 3);
        EXPECT_EQ((Vec2{0, -1}), v1 / 2);
        EXPECT_EQ((Vec2{1, 1}), v2.normalize());
        EXPECT_FLOAT_EQ(std::sqrt(17.0f), Vec2i::distance(v1, v2));
    END

    TEST(functionality, container)
        using namespace utils;

        Container<int> cont;

        EXPECT_EQ(0, cont.size());
        EXPECT_EQ(3, *cont.append(new int{3}));
        EXPECT_EQ(420, *cont.append(new int{420}));
        EXPECT_EQ(2, cont.size());
        EXPECT_EQ(3, *cont.getContainer().front());
    END

    TEST(functionality, parsers)
        using namespace utils::parser;

        /// LevelConfigParser
        EXPECT_THROW(LevelConfigParser{""}, const char*);
        EXPECT_THROW(LevelConfigParser{"nemLetezik"}, const char*);

        LevelConfigParser lcp1 {"test/f/invalid_level.conf"};
        EXPECT_FALSE(lcp1.isLabelValid(false));

        LevelConfigParser lcp2 {"test/f/level.conf"};
        EXPECT_TRUE(lcp2.isLabelValid(false));
        lcp2.parse();

        EXPECT_EQ(4, lcp2.getAttribute("followPath").size());
        EXPECT_EQ((utils::Vec2f{68, -80}), lcp2.getAttribute("followPath")[0]);
        EXPECT_EQ((utils::Vec2f{-810819019.0f, 180.1f}), lcp2.getAttribute("followPath").back());

        EXPECT_EQ(1, lcp2.getAttribute("nestPosition").size());
        EXPECT_EQ((utils::Vec2f{-20.55f, 605}), lcp2.getAttribute("nestPosition")[0]);
        ///

        /// SaveFileParser

        ///

    END

    // app->destroy();

    return 0;
}