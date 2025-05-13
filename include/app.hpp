#pragma once

#ifndef CPORTA

#include "objects/object_base.hpp"
#include "scene.hpp"

namespace pftd {

/*! A renderer. */
class Renderer final
{
    friend class App;
public:
    /**
    * @brief Létrehozza az ablakot a rendering kontextussal együtt.
    *
    * @param width Az ablak szélessége.
    * @param height Az ablak magassága.
    * @param windowTitle Az ablak címe.
    */
    Renderer(unsigned int width, unsigned int height, std::string const& windowTitle);

    Renderer(Renderer const&) = delete;
    Renderer(Renderer&&) = delete;

    /**
    * @brief Felszabadítja az ablak erőforrásait.
    */
    ~Renderer();

    /**
    * @brief Átmásolja a frame buffer-re az `m_queue`-ban tárolt objektumokat.
    */
    void render();

    /**
    * @brief Törli a frame buffer-t.
    */
    void clear() const { m_window->clear(); }

    /**
    * @brief Megjeleníti a frame buffer tartalmát.
    */
    void display() const { m_window->display(); }

    /**
    * @brief Hozzáad az `m_queue`-hoz egy megjelenítendő objektumot.
    *
    * @param o Az objektum amit megjeleníteni szeretnénk.
    */
    void pushQueue(Object const* o) { m_queue.push(o); }

    /**
    * @brief `m_window` getter.
    *
    * @return A kezelt ablak.
    */
    sf::RenderWindow* getWindow() const { return m_window; }

private:
    /*! A kezelt ablak. */
    sf::RenderWindow* m_window = nullptr;

    /*! Az ablak szélessége. */
    unsigned int m_width;

    /*! Az ablak magassága. */
    unsigned int m_height;

    /*! A render queue. */
    std::priority_queue<Object const*, std::vector<Object const*>, Object::Compare> m_queue;

};

/*! Az egész játékért felelő osztály. */
class App final
{
public:
    App(App const&) = delete;
    App(App&&) = delete;

    /**
    * @brief Felszabadítja a kezelt erőforrásokat.
    *
    * Törli a renderer-t, az erőforrás-kezelőt és a nézeteket.
    */
    ~App();

    /**
    * @brief A fő programciklus.
    */
    void run();

    /**
    * @brief Hozzáad egy új nézetet.
    *
    * Ha az `active` igaz, akkor meghívja a `changeScene`-t a megadott `id`-ra.
    * Megjegyzés: Ha már létezik ilyen nézet a megadott azonosítóval, akkor `SceneError`-t dob.
    *
    * @param id A nézet azonosítója.
    * @param scene Maga a nézet osztály egy példánya (pl.: MenuScene, GameScene).
    * @param active Ez legyen e az aktív nézet.
    */
    void addScene(std::string id, Scene* scene, bool active = false);

    /**
    * @brief Nézetet vált (aktívvá tesz egy másikat).
    *
    * Ha megegyezik az eddigi és a kért nézet, akkor nem csinál semmit. Egyébként meg az eddigi nézetet deaktiválja, és az újat pedig aktiválja.
    * Megjegyzés: Ha már létezik ilyen nézet a megadott azonosítóval, akkor `SceneError`-t dob.
    *
    * @param id Az új nézet azonosítója.
    * @param flag Egyéb "kérést" közlő opció flag.
    * @return Sikerült e váltani.
    */
    bool changeScene(std::string id, Scene::StateFlag flag = Scene::StateFlag::NONE);

    /**
    * @brief `m_running` getter.
    *
    * @return Fut e a program.
    */
    auto isRunning() const { return this->m_running; }

    /**
    * @brief
    *
    * @return A programhoz tartozó ablak szélessége.
    */
    int getWindowWidth() const { return this->m_renderer->m_width; }

    /**
    * @brief
    *
    * @return A programhoz tartozó ablak magassága.
    */
    int getWindowHeight() const { return this->m_renderer->m_height; }

    App& operator=(App const&) = delete;

    /**
    * @brief A singleton instance megszerzése.
    *
    * @return Az osztályhoz tartozó singleton instance.
    */
    static App* getInstance() { return m_instance; }

    /**
    * @brief Inicializálja a különböző programelemeket.
    *
    * Megjegyzés: Meg kell hívni a `destroy()`-t, ha már nincs szükség rá!
    *
    * @param width Az ablak szélessége.
    * @param height Az ablak magassága.
    * @param windowTitle Az ablak címe.
    * @return Az osztályhoz tartozó singleton instance.
    */
    static App* create(unsigned int width, unsigned int height, std::string const& windowTitle);

    /**
    * @brief Törli a singleton instance-t.
    */
    static void destroy() { delete m_instance; }

private:
    // Az `m_instance` létrehozásához van használva.
    App() = default;

    /*! A singleton instance. */
    static App* m_instance;

    /*! Fut e a program. */
    bool m_running = false;

    /*! A renderer. */
    Renderer* m_renderer = nullptr;

    /*! A nézetek: [id, nézet]. */
    std::map<std::string, Scene*> m_scenes;

    /*! Az aktív nézet azonosítója. */
    std::string m_activeSceneID;

};

/*! Nézethiba. */
struct SceneError : public std::runtime_error
{
    using std::runtime_error::runtime_error;
};

}

#endif
