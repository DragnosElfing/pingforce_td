#include <stdexcept>

#include "app.hpp"
#include "resources.hpp"
#include "scenes/menu.hpp"
#include "scenes/game.hpp"
#include "utils/logger.hpp"

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
    // Muszáj kondícionálisan, mert lehet (valójában biztos hogy nem, de meh) hogy sose volt meghívva az App::create
    if(m_renderer) delete m_renderer;
    ResourceManager::destroy();
    for(auto& [_, scene] : m_scenes) {
        delete scene;
    }
}

// Singleton instance
App* App::m_instance = nullptr;
// Muszáj App::destroy-t hívni ha már nem dolgozunk vele
App* App::create(unsigned int width, unsigned int height, std::string const& title)
{
    // Ha már egyszer létre volt hozva
    if(m_instance) {
        delete m_instance;
    }
    m_instance = new App();
    auto& I = m_instance;
    
    I->m_renderer = new Renderer{width, height, title};

    ResourceManager::create();
    if(!ResourceManager::getInstance()->loadDefaultFont("res/fonts/Gorditas/Gorditas-Bold.ttf")) {
        throw "Nem lehetett megnyitni a betűtípust!";
    }

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

    auto const clickEvent = [this](sf::Event::MouseButtonPressed const& ev)
    {
        //auto& m = ev.position;

        m_scenes[m_activeSceneID]->onEvent(ev);
    };

    while(isRunning()) {
        m_renderer->m_window->handleEvents(closeEvent, clickEvent);
        for(auto& obj : m_scenes[m_activeSceneID]->getObjects()) {
            m_renderer->pushQueue(obj);
        }
        m_renderer->render();
    }
}

void App::addScene(std::string id, Scene* scene, bool setActive)
{
    // Ha már van ilyen ID
    if(m_scenes.find(id) != m_scenes.end()) {
        throw SceneError{"Használt ID."};
    }

    m_scenes[id] = scene;
    if(setActive) {
        m_activeSceneID = id; 
    }
}

bool App::changeScene(std::string newID)
{
    if(m_activeSceneID == newID) return false;
    if(m_scenes.find(newID) == m_scenes.end()) throw SceneError{"Nincs ilyen scene."};

    m_activeSceneID = newID;
    return true;
}
///
