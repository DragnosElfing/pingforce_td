#include "scene.hpp"
#include "resources.hpp"

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
        throw LoadError{"Nem lehetett a hangfájlt megnyitni: " + source + '.'};
    }

    backgroundMusic->setLooping(true);
    backgroundMusic->setVolume(volume);
}

void Scene::toggleActive(SceneStateFlag)
{
    isActive = !isActive;

    // Alapból egy nézet legfeljebb zenét indít/állít meg.
    if(isActive) {
        if(backgroundMusic) {
            backgroundMusic->play();
        }
    } else {
        backgroundMusic->stop();
    }
}
