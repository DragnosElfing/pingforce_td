#pragma once

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/System/Vector2.hpp"
#include "resources.hpp"
#include "scene.hpp"

namespace pftd
{

class GameScene final : public Scene
{
public:
    GameScene(ResourceManager&);
    ~GameScene();

    void onEvent(sf::Event const& ev) override;
};

}