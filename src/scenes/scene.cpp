#include "scene.hpp"

using namespace pftd;

Scene::~Scene()
{
    if(backgroundMusic) delete backgroundMusic;
    for(auto& object : this->getObjects()) {
        delete object;
    }
}

void Scene::setMusic(std::string const& source, float volume)
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
    backgroundMusic->setVolume(volume);
}

bool Scene::setActive(bool active)
{
    if(active == isActive) return false;
    isActive = active;

    if(active) {
        if(backgroundMusic) {
            backgroundMusic->play();
        }
    } else {
        backgroundMusic->stop();
    }

    return true;
}
