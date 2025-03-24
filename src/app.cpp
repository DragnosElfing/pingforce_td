#include <filesystem>
#include <stdexcept>

#include "SFML/Audio.hpp"

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
        m_scenes[m_activeSceneID]->onEvent(ev);
    };

    sf::Clock clock;
    while(isRunning()) {
        m_renderer->m_window->handleEvents(closeEvent, clickEvent);
        m_scenes[m_activeSceneID]->update(clock.restart().asSeconds());
        for(auto& obj : m_scenes[m_activeSceneID]->getObjects()) {
            m_renderer->pushQueue(obj);
        }
        m_renderer->render();
    }
}

bool App::changeScene(std::string newID)
{
    if(m_activeSceneID == newID) return false;

    if(m_scenes.find(newID) == m_scenes.end()) throw SceneError{"Nincs ilyen scene."};

    // A default érték, amikor még nincs egy scene sem
    if(!m_activeSceneID.empty()) {
        m_scenes[m_activeSceneID]->setActive(false);
    }
    m_activeSceneID = newID;
    m_scenes[newID]->setActive(true);

    return true;
}

void App::addScene(std::string id, Scene* scene, bool setActive)
{
    // Ha már van ilyen ID
    if(m_scenes.find(id) != m_scenes.end()) {
        throw SceneError{"Használt ID."};
    }

    m_scenes[id] = scene;
    if(setActive) {
        this->changeScene(id); 
    }
}

///
