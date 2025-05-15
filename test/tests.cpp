#include "modified_gtest_lite.hpp"

#include "utils/hetero_collection.hpp"
#include "utils/substitute_types.hpp"
#include "utils/parsers.hpp"
#include "mock/app.hpp"
#include "mock_scenes/game.hpp"
#include "mock_scenes/menu.hpp"
#include "mock/rman.hpp"
#include "mock_objects/mock_entities/all_entities.hpp"

using namespace pftd;
using namespace pftd::utils;
using namespace pftd_test;

int main()
{
    // A teszteléshez minden adattag & metódus publikus.
    // Egyes osztályok helyességét 100%-ig SFML nélkül nem lehet tesztelni. Az ilyen osztályok metódusai csak "kiabálnak."
    // Ezért NEM egyeznek meg teljesen a valódi osztályokkal!

    /// UTILS
    // Ezeket viszont teljesen lehet tesztelni.
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
        EXPECT_THROW(LevelConfigParser{""}, ParseError);
        EXPECT_THROW(LevelConfigParser{"nemLetezik"}, ParseError);
        EXPECT_THROW(LevelConfigParser{"test/f/empty.txt"}.parse(), ParseError);

        LevelConfigParser lcp1 {"test/f/invalid_level.conf"};
        EXPECT_FALSE(lcp1.isLabelValid(false));

        LevelConfigParser lcp2 {"test/f/valid_level.conf"};
        EXPECT_TRUE(lcp2.isLabelValid(false));
        EXPECT_NO_THROW(lcp2.parse());
        EXPECT_EQ(4, lcp2.getAttribute("followPath").size());
        EXPECT_EQ((Vec2f{68, -80}), lcp2.getAttribute("followPath").at(0));
        EXPECT_EQ((Vec2f{-810819019.0f, 180.1f}), lcp2.getAttribute("followPath").back());
        EXPECT_EQ(1, lcp2.getAttribute("nestPosition").size());
        EXPECT_EQ((Vec2f{-20.55f, 605}), lcp2.getAttribute("nestPosition").at(0));
        ///

        /// SaveFileParser
        EXPECT_THROW(SaveFileParser{""}, ParseError);
        EXPECT_THROW(SaveFileParser{"nemLetezik"}, ParseError);
        EXPECT_THROW(SaveFileParser{"test/f/empty.txt"}.parse(), ParseError);
        EXPECT_THROW(SaveFileParser{"test/f/invalid_save.dat"}.parse(), ParseError);

        SaveFileParser sfp2 {"test/f/valid_save.dat"};
        EXPECT_TRUE(sfp2.isLabelValid(false));
        EXPECT_NO_THROW(sfp2.parse());
        auto stats = sfp2.getStats();
        EXPECT_EQ(5400, stats.score);
        EXPECT_EQ(1650, stats.wealth);
        EXPECT_EQ(5, stats.maxHp);
        EXPECT_EQ(3, stats.hp);
        auto entities = sfp2.getEntities();
        EXPECT_EQ(5, entities.size());
        EXPECT_EQ(static_cast<unsigned int>(SaveFileParser::EntityType::TOWER), static_cast<unsigned int>(entities.front().entityType));
        EXPECT_FLOAT_EQ(0.02f, entities.at(3).seal.lerpParam);
        EXPECT_EQ(0, entities.back().proj.projID);
    END
    ///

    /// APP
    // Minden lényeges, tesztelhető funkcionalitást lefednek.
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
        EXPECT_TRUE(resMan->loadDefaultFont("test/f/test.ttf"))
            << "Nem sikerült betölteni a betűtípust!\n";
        EXPECT_TRUE(resMan->getTexture("test/f/test.png"))
            << "Nem sikerült betölteni a teszt sprite-ot!";
        EXPECT_TRUE(resMan->getSound("test/f/test.mp3"))
            << "Nem sikerült betölteni a gomb kattintás hangeffektet!";

        EXPECT_FALSE(resMan->loadDefaultFont("nemLetezik"));
        EXPECT_THROW(resMan->getSound("nemLetezik"), LoadError);
        EXPECT_THROW(resMan->getTexture("nemLetezik"), LoadError);

    END

    /// SCENES
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
    ///

    /// SERIALIZE
    TEST(all, serialize)
        using namespace utils::parser;
        std::fstream sTestF {"test/f/serializable_test.dat", std::ios_base::out};

        Level::Stats stats {3, 2, 50, 700};
        stats.serialize(sTestF);

        sTestF << '\n';

        auto tower = Snowballer{{100.0f, 100.0f}};
        tower.serialize(sTestF);

        FollowPath followPath {};
        EXPECT_NO_THROW(followPath.append(new utils::Vec2f{70.0f, -70.0f}));
        auto enemy = FZC{followPath};
        enemy.serialize(sTestF);

        auto projectile = Snowball{{10.0f, 50.0f}, {1.0f, 0.0f}, 1.0f};
        projectile.serialize(sTestF);

        sTestF.close();

        SaveFileParser sTestParser {"test/f/serializable_test.dat"};
        EXPECT_EQ(stats.score, sTestParser.get<unsigned int>());
        for(size_t _ = 0U; _ < 3; ++_) {
            EXPECT_NO_THROW(sTestParser.get<int>());
        }

        // Tower
        EXPECT_EQ(std::string{"penguin"}, sTestParser.get<std::string>());
        EXPECT_EQ(static_cast<int>(tower.properties.id), sTestParser.get<int>());
        EXPECT_EQ((utils::Vec2f{100, 100}), sTestParser.get<utils::Vec2f>());

        // Seal
        EXPECT_EQ(std::string{"seal"}, sTestParser.get<std::string>());
        EXPECT_EQ(static_cast<int>(enemy.id), sTestParser.get<int>());
        auto enemyPos = sTestParser.get<utils::Vec2f>();
        EXPECT_NE(followPath.getContainer().front()->x, enemyPos.x);
        EXPECT_NE(followPath.getContainer().front()->y, enemyPos.y);
        EXPECT_FLOAT_EQ(0.0f, sTestParser.get<float>());
        EXPECT_FALSE(sTestParser.get<bool>());
        EXPECT_EQ(enemy.hp, sTestParser.get<int>());

        // Projectile
        EXPECT_EQ(std::string{"projectile"}, sTestParser.get<std::string>());
        EXPECT_EQ(static_cast<int>(projectile.id), sTestParser.get<int>());
        auto projPos = sTestParser.get<utils::Vec2f>();
        EXPECT_FLOAT_EQ(projectile.getPosition().x, projPos.x);
        EXPECT_FLOAT_EQ(projectile.getPosition().y, projPos.y);
        auto projDir = sTestParser.get<utils::Vec2f>();
        EXPECT_FLOAT_EQ(projectile.direction.x, projDir.x);
        EXPECT_FLOAT_EQ(projectile.direction.y, projDir.y);
        EXPECT_FLOAT_EQ(projectile.linearSpeed, sTestParser.get<float>());
    END
    ///

    /// LEVEL
    Level* level = nullptr;
    TEST(save_and_reset, level)
        using namespace utils::parser;

        level = new Level{"test/f/level_save.dat", Level::Stats{3, 3, 0, 250}};
        // Teszteljük, mint a `functionality.parsers`-nél.
        EXPECT_EQ(4, level->config.getAttribute("followPath").size());
        EXPECT_EQ((Vec2f{68, -80}), level->config.getAttribute("followPath").at(0));
        EXPECT_EQ((Vec2f{-810819019.0f, 180.1f}), level->config.getAttribute("followPath").back());
        EXPECT_EQ(1, level->config.getAttribute("nestPosition").size());
        EXPECT_EQ((Vec2f{-20.55f, 605}), level->config.getAttribute("nestPosition").at(0));

        EXPECT_NO_THROW(level->save());

        SaveFileParser sfp {"test/f/level_save.dat"};
        EXPECT_NO_THROW(sfp.parse());
        auto sStats = sfp.getStats();
        EXPECT_EQ(level->stats.maxHp, sStats.maxHp);
        EXPECT_EQ(level->stats.money, sStats.wealth);
        EXPECT_EQ(0, sfp.getEntities().size());

        level->towers.push_back(new Snowballer{});
        EXPECT_EQ(1, level->towers.size());
        level->reset(Level::Stats{1, 1, 0, 0});
        EXPECT_EQ(0, level->towers.size());
        EXPECT_EQ(0, level->stats.money);
    END

    TEST(select, level)
        Tower* tower = new IcicleStabber{{100.0f, 100.0f}};
        level->selectTower(tower->clone());
        EXPECT_EQ(static_cast<int>(tower->properties.id), static_cast<int>(level->selectedTower->properties.id));
        level->deselectTower();
        EXPECT_EQ((Tower*)nullptr, level->selectedTower);

        level->reset(Level::Stats(3, 3, 0, 10'000));
        level->selectTower(tower->clone());
        EXPECT_TRUE(level->placeTower())
            << "Elengedő fedezettel sem sikerült letenni a tornyot!";
        EXPECT_GT(10'000, level->stats.money)
            << "Nem lett levonva a torony ára!";
        level->reset(Level::Stats(3, 3, 0, 0));
        level->selectTower(tower->clone());
        EXPECT_FALSE(level->placeTower())
            << "NEM elengedő fedezettel sikerült letenni a tornyot!";

        Tower* tower2 = new Snowballer{{100.0f, 100.0f}};
        level->reset(Level::Stats(3, 3, 0, 10'000));
        level->selectTower(tower->clone());
        EXPECT_TRUE(level->placeTower());
        level->selectTower(tower2->clone());
        EXPECT_FALSE(level->placeTower())
            << "Egymáshoz túl közel is sikerült letenni két tornyot!";

        delete tower2;
        delete tower;
    END

    TEST(enemy_spawning, level)
        for(size_t _ = 0; _ < 10; ++_) {
            level->spawnSeal();
        }
        EXPECT_EQ(10, level->seals.size())
            << "Ellenfél spawnolás nem működik helyesen!";
        // Fölösleges tesztelni, hogy milyen típusú ellenfélt sikerült, hisz nem használunk véletlent a tesztekben.
    END

    TEST(update_seals, level)
        level->reset(Level::Stats(3, 3, 0, 10'000));

        // Végigmegy.
        level->spawnSeal();
        level->_updateSeals(0.001f); // 1 ms-es lépés.
        auto enemy = level->seals.front();
        EXPECT_FALSE(enemy->lerpParam < 1.0f && enemy->hasCompletedPath());
        EXPECT_FALSE(enemy->lerpParam < 1.0f && enemy->hasReachedNest());
        EXPECT_EQ(3, level->stats.hp);
        enemy->lerpParam = 1.0f;
        level->_updateSeals(0.001f); // Duplán kellenek, mert a Level csak késleltetve reagál a változásokra (az `enemy->update(dt)` csak minden check után van).
        level->_updateSeals(0.001f);
        EXPECT_EQ(2, level->stats.hp);
        enemy->lerpParam = 0.0f;
        level->_updateSeals(0.001f);
        level->_updateSeals(0.001f);
        EXPECT_EQ(0, level->seals.size());

        // Meghal.
        level->spawnSeal();
        enemy = level->seals.front();
        EXPECT_LT(0, enemy->hp);
        while(enemy->hp > 0) {
            enemy->damage();
        }
        level->update(0.001f);
        EXPECT_EQ(0, level->seals.size());
    END

    TEST(update_projectiles, level)
        // Kimegy a képernyőből.
        level->projectiles.push_back(new Snowball{{200, 200}, {std::sqrt(2.0f), -std::sqrt(2.0f)}, 1'000'000});
        level->_updateProjectiles(0.001f);
        level->_updateProjectiles(0.001f);
        EXPECT_EQ(0, level->projectiles.size());

        // Ütközik.
        level->spawnSeal();
        auto enemy = level->seals.front();
        int enemyMaxHp = enemy->hp;
        enemy->setPosition({100.0f, 100.0f});
        level->projectiles.push_back(new Snowball{{180.0f, 100.0f}, {-1.0f, 0.0f}, 1});
        level->_updateProjectiles(0.001f);
        level->_updateProjectiles(0.001f);
        // Működik, mert közelebb mint 100 egységre vannak egymástól (ez hard-coded érték volt, és végül az maradt).
        EXPECT_LT(enemy->hp, enemyMaxHp);
        EXPECT_EQ(0, level->projectiles.size());
    END
    if(level) delete level;
    ///

    app->destroy();
    ///

    return 0;
}
