#include "app.hpp"
#include "resources.hpp"
#include "scenes/menu.hpp"
#include "scenes/game.hpp"

using namespace pftd;

int main()
{
    // App létrehozása (`App::destroy()`-t a legvégén meg kell hívni)
    App::create(1440, 810, "PingForce TD");

    // Ne kelljen olyan sokat írni
    auto instance = App::getInstance();
    
    // Nézetek hozzáadása (ezáltal könnyen lehet további nézeteket is létrehozni/hozzáadni)
    instance->addScene("menu", new MenuScene(), true);
    instance->addScene("game", new GameScene());
    
    // Futtatás
    instance->run();
    
    // App törlése
    instance->destroy();

    return 0;
}
