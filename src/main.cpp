#include "app.hpp"
#include "scenes/menu.hpp"
#include "scenes/game.hpp"

#ifdef MEMTRACE
    #include "memtrace.h"
#endif

using namespace pftd;

int main()
{
    // App létrehozása (`App::destroy()`-t a legvégén meg kell hívni)
    App::create(500, 300, "PingForce TD");

    // Ne kelljen olyan sokat írni
    auto instance = App::getInstance();
    auto resourceManager = instance->getResourceManager();
    
    // Nézetek hozzáadása (ezáltal könnyen lehet további nézeteket is létrehozni/hozzáadni)
    instance->addScene("menu", new MenuScene(*resourceManager), true);
    instance->addScene("game", new GameScene(*resourceManager));
    
    // Futtatás
    instance->run();
    
    // App törlése
    instance->destroy();

    return 0;
}
