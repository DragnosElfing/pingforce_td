#include "gtest_lite.h"

// memtrace miatt :(
#undef delete

#include "app.hpp"
#include "scenes/game.hpp"
#include "scenes/menu.hpp"

using namespace pftd;

int main()
{
    // A teszteléshez minden adattag & metódus publikus.

    App::create(1440, 810, "TEST");
    auto app = App::getInstance();

    TEST(resource_checks, core)
        auto resMan = ResourceManager::getInstance();

        // Csak párat tesztelünk: mindenféle load helyesen működik e.
        // Létezik e a fájl amit beakarunk tölteni / már el van tárolva.
        EXPECT_TRUE(resMan->loadDefaultFont("res/fonts/Gorditas/Gorditas-Bold.ttf")) 
            << "Nem sikerült betölteni a betűtípust!\n";
        EXPECT_TRUE(resMan->getTexture("res/images/eggs.png"))
            << "Nem sikerült betölteni a tojások sprite-ját!";
        EXPECT_TRUE(resMan->getSound("res/audio/buttonpress.mp3"))
            << "Nem sikerült betölteni a gomb kattintás hangeffektet!";
        
    END

    TEST(scene_test, core)
        auto gameScene = new GameScene{};
        auto menuScene = new MenuScene{};
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

    app->destroy();

    return 0;
}