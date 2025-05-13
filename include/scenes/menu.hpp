#pragma once

#ifndef CPORTA

#include "objects/gui/button.hpp"
#include "scene.hpp"

namespace pftd {

/*! Menü nézet. */
class MenuScene final : public Scene
{
public:
    MenuScene();
    ~MenuScene() = default;

    void onEvent(sf::Event const& event) override;

    void update(float dt) override;

    void toggleActive(Scene::StateFlag flag = Scene::StateFlag::NONE) override;

private:
    /*! Gombok. */
    std::vector<gr::Button*> m_buttons;

    /**
    * @brief Megnézi, hogy elérhető e a mentés fájl (`GameScene::SAVE_FILE_PATH` alapján).
    *
    * @return Elérhető e a fájl.
    */
    bool _isSaveFileAvailable();

};

}

#endif
