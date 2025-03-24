#include "scene.hpp"

using namespace pftd;

Scene::~Scene()
{
    if(backgroundMusic) delete backgroundMusic;
}

void Scene::setMusic(std::string const& source)
{
    if(backgroundMusic) {
        backgroundMusic->stop();
        delete backgroundMusic;
    }

    backgroundMusic = new sf::Music{};
    if(!backgroundMusic->openFromFile(source)) {
        throw "Nem lehetett a hangfájlt megnyitni!";
    }

    backgroundMusic->setLooping(true);
}

// TODO: should add and clear m_objects
bool Scene::setActive(bool active)
{
    if(active == isActive) return false;
    isActive = active;

    if(active && backgroundMusic) {
        backgroundMusic->play();
    } else {
        backgroundMusic->stop();
    }

    return true;
}
