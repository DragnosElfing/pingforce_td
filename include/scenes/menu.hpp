#pragma once

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

#include "resources.hpp"
#include "scene.hpp"
#include "objects/gui/button.hpp"

namespace pftd
{

class MenuScene final : public Scene
{
public:

    MenuScene(ResourceManager&);
    ~MenuScene();

    void onEvent(sf::Event const&) override;

private:
    // sf::Sprite m_logo;
    // sf::Sprite m_background;
    gui::Button m_newGameButt;
    // gui::Button m_loadGameButt;
};

}