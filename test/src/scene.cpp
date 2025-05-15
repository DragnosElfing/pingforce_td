#include "mock/scene.hpp"

using namespace pftd_test;

Scene::~Scene()
{
    for(auto& object : this->getObjects()) {
        delete object;
    }
}

void Scene::setMusic(std::string const&, float)
{
    where();
}

bool Scene::toggleActive(Scene::StateFlag)
{
    isActive = !isActive;

    // Alapból egy nézet legfeljebb zenét indít/állít meg.
    // Ezt nem tudjuk tesztelni.

    return isActive;
}
