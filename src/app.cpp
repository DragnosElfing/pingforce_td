#include "all.hpp"
#include "app.hpp"

#include "resources.hpp"

using namespace pftd;

/// Renderer
Renderer::Renderer(unsigned int width, unsigned int height, std::string const& title):
    m_width{width}, m_height{height}
{
    m_window = new sf::RenderWindow{sf::VideoMode{{m_width, m_height}}, 
        title, sf::Style::Default, sf::State::Windowed};
}

Renderer::~Renderer()
{
    delete m_window;
}

void Renderer::render()
{
    this->clear();
    
    // Megrajzolunk minden - a queue-ba helyezett - programelemet.
    while(!m_queue.empty()) {
        auto& obj = m_queue.top();
        obj->draw(*m_window, {});
        m_queue.pop();
    }

    this->display();
}

/// App
App::~App()
{
    m_running = false;

    // Muszáj kondícionálisan, mert lehet (valójában biztos hogy nem, de meh) hogy sose volt meghívva az `App::create`.
    if(m_renderer) delete m_renderer;
    for(auto& [_, scene] : m_scenes) {
        delete scene;
    }
    ResourceManager::destroy();
}

// Singleton instance
App* App::m_instance = nullptr;
// Muszáj App::destroy-t hívni ha már nem dolgozunk vele.
App* App::create(unsigned int width, unsigned int height, std::string const& title)
{
    // Ha már egyszer létre volt hozva.
    if(m_instance) {
        delete m_instance;
    }
    m_instance = new App();
    auto& I = m_instance;
    
    I->m_renderer = new Renderer{width, height, title};

    // ResourceManagerrel betöltjük a használt betűtípust (csak ezt az egy van használatban).
    ResourceManager::create();
    ResourceManager::getInstance()->loadDefaultFont("res/fonts/Gorditas/Gorditas-Bold.ttf");

    I->m_running = true;

    return getInstance();
}

void App::run()
{
    auto const closeEvent = [this](sf::Event::Closed const& ev)
    {
        m_running = false;

        m_scenes[m_activeSceneID]->onEvent(ev);
    };

    auto const mouseMoveEvent = [this](sf::Event::MouseMoved const& ev)
    {
        m_scenes[m_activeSceneID]->onEvent(ev);
    };

    auto const keyPressEvent = [this](sf::Event::KeyPressed const& ev)
    {
        m_scenes[m_activeSceneID]->onEvent(ev);
    };

    auto const clickEvent = [this](sf::Event::MouseButtonPressed const& ev)
    {
        m_scenes[m_activeSceneID]->onEvent(ev);
    };
    // Más fajta event-et nem kezelnek a nézetek.

    sf::Clock clock;
    while(isRunning()) {
        // Események delegálása.
        m_renderer->getWindow()->handleEvents(closeEvent, clickEvent, mouseMoveEvent, keyPressEvent);
        
        // Aktív nézet frissítése.
        m_scenes[m_activeSceneID]->update(clock.restart().asSeconds());

        // Megjeleníteni kívánt elemek queue-ba helyezése, majd pedig render.
        for(auto& obj : m_scenes[m_activeSceneID]->getObjects()) {
            if(!obj) continue; // Véletlenül se.
            m_renderer->pushQueue(obj);
        }
        m_renderer->render();
    }
}

bool App::changeScene(std::string newID, SceneStateFlag flag)
{
    // Már ez a nézet aktív.
    if(m_activeSceneID == newID) return false;

    // Hiba: nincs ilyen nézet!
    if(m_scenes.find(newID) == m_scenes.end()) {
        throw SceneError{"Nincs ilyen nézet."};
    }

    // Ha nem volt még aktív nézet, akkor azt nem kell deaktiválni (a nagy semmit).
    if(!m_activeSceneID.empty()) {
        m_scenes[m_activeSceneID]->toggleActive(flag);
    }

    // Actual nézetváltás.
    m_activeSceneID = newID;
    m_scenes[newID]->toggleActive(flag);

    return true;
}

void App::addScene(std::string id, Scene* scene, bool setActive)
{
    // Hiba: már van ilyen ID.
    if(m_scenes.find(id) != m_scenes.end()) {
        throw SceneError{"Használt ID."};
    }

    m_scenes[id] = scene;
    if(setActive) {
        this->changeScene(id); 
    }
}

///
