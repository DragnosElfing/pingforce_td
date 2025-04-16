#pragma once

#include "all.hpp"

#include "objects/object_base.hpp"
#include "scene.hpp"

namespace pftd {

class Renderer final
{
    friend class App;
public:
    Renderer(unsigned int, unsigned int, std::string const&);
    Renderer(Renderer const&) = default;
    Renderer(Renderer&&) = default;
    ~Renderer();

    void render();
    void clear() const { m_window->clear(); }
    void display() const { m_window->display(); }
    void pushQueue(Object const* o) { m_queue.push(o); }
    sf::RenderWindow* getWindow() const { return m_window; }
private:
    sf::RenderWindow* m_window = nullptr;
    unsigned int m_width;
    unsigned int m_height;
    std::priority_queue<Object const*, std::vector<Object const*>, Object::Compare> m_queue;
};

class App final
{
public:
    App(App const&) = delete;
    App(App&&) = delete;
    ~App();

    void run();
    void addScene(std::string id, Scene* scene, bool active = false);
    [[maybe_unused]]
    bool changeScene(std::string id);
    auto isRunning() const { return this->m_running; }
    auto getResourceManager() const { return this->m_resManager; }
    int getWindowWidth() const { return this->m_renderer->m_width; }
    int getWindowHeight() const { return this->m_renderer->m_height; }

    App& operator=(App const&) = delete;
    
    [[nodiscard]]
    static App* getInstance() { return m_instance; }
    [[maybe_unused]]
    static App* create(unsigned int, unsigned int, std::string const&);
    static void destroy() { delete m_instance; }
private:
    App() = default;

    static App* m_instance;

    bool m_running = false;
    ResourceManager* m_resManager = nullptr;
    Renderer* m_renderer = nullptr;
    std::map<std::string, Scene*> m_scenes;
    std::string m_activeSceneID;
};

struct SceneError : public std::runtime_error
{
    using std::runtime_error::runtime_error;
};

}
