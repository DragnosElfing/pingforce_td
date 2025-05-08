#pragma once

#include "objects/gui/button.hpp"
#include "scene.hpp"

namespace pftd
{

/*! Menü nézet. */
class MenuScene final : public Scene
{
public:
    MenuScene();
    ~MenuScene();

    /**
    * @brief Delegált események kezelése.
    *
    * @param event Kezelni kívánt esemény.
    */
    void onEvent(sf::Event const& event) override;

    /**
    * @brief Update.
    *
    * @param dt Delta idő.
    */
    void update(float dt) override;

    void toggleActive(SceneStateFlag flag = SceneStateFlag::NONE) override;

private:
    /*! Gombok. */
    std::vector<gr::Button*> m_buttons;
    
};

}