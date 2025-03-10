#pragma once

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/System/Vector2.hpp"

#include "objects/gui/image.hpp"
#include "resources.hpp"
#include "scene.hpp"

namespace pftd
{

class GameScene final : public Scene
{
public:
    GameScene();
    ~GameScene();

    void onEvent(sf::Event const& ev) override;

private:
    gui::Image m_testImage;

};

}