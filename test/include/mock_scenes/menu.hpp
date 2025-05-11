#pragma once

#include "mock_objects/mock_gui/button.hpp"
#include "mock/scene.hpp"

namespace pftd_test
{

/*! Menü nézet tesztelésre szánt változata. */
class MenuScene final : public Scene
{
public:
    MenuScene();
    ~MenuScene();

    void onEvent(int event) override;
    void update(float dt) override;

//private:
    std::vector<gr::Button*> m_buttons;

};



}
