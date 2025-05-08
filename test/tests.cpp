#include "gtest_lite.h"

// memtrace miatt: nem tudja értelmezni a delete-elt metódusokat
#undef new
#undef delete

#include "utils/hetero_collection.hpp"
#include "utils/substitute_types.hpp"
#include "utils/parsers.hpp"
#include "mock_app.hpp"
#include "scenes/mock_game.hpp"
#include "scenes/mock_menu.hpp"
#include "mock_rman.hpp"

// // újradefiniáljuk memtrace szerint
// #define new new(__LINE__, __FILE__)
// #define delete memtrace::set_delete_call(__LINE__, __FILE__),delete

using namespace pftd;
using namespace pftd::utils;
using namespace pftd_test;

int main()
{
    // A teszteléshez minden adattag & metódus publikus.
    // Egyes osztályok helyességét 100%-ig SFML nélkül nem lehet tesztelni.
    // Az ilyen osztályok metódusai csak "kiabálnak."

    App::create(1440, 810, "TEST");
    auto app = App::getInstance();

    TEST(base, core)
        EXPECT_TRUE(app->m_running)
            << "Nem sikerült elindulnia a programnak!";
        EXPECT_TRUE(app->m_activeSceneID.empty())
            << "Valamilyen nézet aktív, aminek nem kéne!";
    END

    TEST(resource_checks, core)
        auto resMan = ResourceManager::getInstance();

        // Csak párat tesztelünk: mindenféle load helyesen működik e.
        // Létezik e a fájl amit beakarunk tölteni / már el van tárolva.
        EXPECT_TRUE(resMan->loadDefaultFont("test/f/Gorditas-Bold.ttf")) 
            << "Nem sikerült betölteni a betűtípust!\n";
        EXPECT_TRUE(resMan->getTexture("test/f/eggs.png"))
            << "Nem sikerült betölteni a tojások sprite-ját!";
        EXPECT_TRUE(resMan->getSound("test/f/buttonpress.mp3"))
            << "Nem sikerült betölteni a gomb kattintás hangeffektet!";
        
    END

    auto gameScene = new GameScene{};
    auto menuScene = new MenuScene{};
    TEST(scene_test, core)
        app->addScene("game", gameScene, true);
        app->addScene("menu", menuScene);

        // Hamist kell visszaadnia, mert már aktív ez a nézet.
        EXPECT_FALSE(app->changeScene("game"));

        EXPECT_TRUE(app->changeScene("menu"));
    
        EXPECT_THROW(app->addScene("game", nullptr), SceneError)
            << "Nincs helyesen kezelve a nézet hozzáadás!";
        EXPECT_THROW(app->changeScene("nincsIlyen"), SceneError)
            << "Nincs helyesen kezelve a nézetváltás!";
    END

    TEST(button_click, scenes)
        // Csak a menüben teszteljük: ha itt működik, akkor a játék nézetben is fog.
        app->changeScene("menu");

        bool clickNewGame = false;
        bool clickLoadGame = false;
        // Kettő gombnak kell lennie: új játék és mentett betöltése.
        menuScene->m_buttons.front()->setCallback([&clickNewGame](){
            clickNewGame = true;
        });
        menuScene->m_buttons.back()->setCallback([&clickLoadGame](){
            clickLoadGame = true;
        });

        menuScene->m_buttons.front()->handleClick({100, 100});
        EXPECT_TRUE(clickNewGame);
        EXPECT_FALSE(clickLoadGame);
    END

    // ...

    TEST(functionality, vec2)

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
        EXPECT_EQ((Vec2f{68, -80}), lcp2.getAttribute("followPath")[0]);
        EXPECT_EQ((Vec2f{-810819019.0f, 180.1f}), lcp2.getAttribute("followPath").back());

        EXPECT_EQ(1, lcp2.getAttribute("nestPosition").size());
        EXPECT_EQ((Vec2f{-20.55f, 605}), lcp2.getAttribute("nestPosition")[0]);
        ///

        /// SaveFileParser
        EXPECT_THROW(SaveFileParser{""}, const char*);
        EXPECT_THROW(SaveFileParser{"nemLetezik"}, const char*);

        SaveFileParser sfp1 {"test/f/invalid_save.dat"};
        EXPECT_FALSE(sfp1.isLabelValid(false));

        SaveFileParser sfp2 {"test/f/save.dat"};
        EXPECT_TRUE(sfp2.isLabelValid(false));
        sfp2.parse();

        auto stats = sfp2.getStats();
        EXPECT_EQ(200, stats.score);
        EXPECT_EQ(250, stats.wealth);
        EXPECT_EQ(2, stats.hp);

        auto entities = sfp2.getEntities();
        EXPECT_EQ(3, entities.size());
        //EXPECT_EQ((SaveFileParser::EntityType::TOWER), entities.back().entityType);
        EXPECT_EQ(1, entities.back().towerID);
        ///

    END

    app->destroy();

    return 0;
}