#pragma once

#include "objects/gui/image.hpp"
#include "objects/gui/button.hpp"
#include "scene.hpp"
#include "resources.hpp"

namespace pftd
{

class MenuScene final : public Scene
{
public:
    MenuScene();
    ~MenuScene();

    void onEvent(sf::Event const&) override;
    void update(float dt) override;

private:
    //gr::Sprite m_logo;
    //gr::Sprite m_background;
    //gr::Label m_acknowledgement;
    // gr::Button m_newGameButt;
    // gr::Button m_loadGameButt;
    std::vector<gr::Button*> m_buttons;
};

}