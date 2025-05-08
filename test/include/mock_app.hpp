#pragma once

#include "objects/mock_object_base.hpp"
#include "mock_scene.hpp"

namespace pftd_test {

/*! A tesztelésre használt renderer: funkcionalitása majdnem megegyezik a valódiéval, de valójában nem jelenít meg semmit. */
class Renderer final
{
    friend class App;
public:
    Renderer(unsigned int width, unsigned int height, std::string const& windowTitle);

    Renderer(Renderer const&) = delete;
    Renderer(Renderer&&) = delete;
    
    ~Renderer();

    void render();
    void clear() const;
    void display() const;
    void pushQueue(Object const* o) { m_queue.push(o); }
    void getWindow() const;

//private:
    unsigned int m_width;
    unsigned int m_height;
    std::priority_queue<Object const*, std::vector<Object const*>, Object::Compare> m_queue;

};

/*! Az egész játékért felelő osztály tesztelésre szánt változata. */
class App final
{
public:
    App(App const&) = delete;
    App(App&&) = delete;

    ~App();

    void run();
    void addScene(std::string id, Scene* scene, bool active = false);
    bool changeScene(std::string id);
    auto isRunning() const { return this->m_running; }
    int getWindowWidth() const { return this->m_renderer->m_width; }
    int getWindowHeight() const { return this->m_renderer->m_height; }

    App& operator=(App const&) = delete;

    static App* getInstance() { return m_instance; }
    static App* create(unsigned int width, unsigned int height, std::string const& windowTitle);
    static void destroy() { delete m_instance; }

//private:
    App() = default;

    static App* m_instance;
    bool m_running = false;
    Renderer* m_renderer = nullptr;
    std::map<std::string, Scene*> m_scenes;
    std::string m_activeSceneID;

};

/*! Nézethiba. */
struct SceneError : public std::runtime_error
{
    using std::runtime_error::runtime_error;
};

}
