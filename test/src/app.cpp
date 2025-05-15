#include "mock/app.hpp"
#include "mock/rman.hpp"

using namespace pftd_test;

/// Renderer
Renderer::Renderer(unsigned int width, unsigned int height, std::string const&):
    m_width{width}, m_height{height}
{
    where();
}

Renderer::~Renderer()
{
    where();
}

void Renderer::render()
{
    this->clear();

    // Megrajzolunk minden - a queue-ba helyezett - programelemet.
    while(!m_queue.empty()) {
        //auto& obj = m_queue.top();
        m_queue.pop();
    }

    this->display();
}

/// App
App::~App()
{
    m_running = false;

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
    ResourceManager::getInstance()->loadDefaultFont("test/f/Gorditas-Bold.ttf");

    I->m_running = true;

    return getInstance();
}

void App::run()
{
    where();
}

bool App::changeScene(std::string newID, Scene::StateFlag flag)
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
