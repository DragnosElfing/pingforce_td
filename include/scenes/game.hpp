#pragma once

#include <utility>
#include <vector>

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/System/Vector2.hpp"

#include "objects/entity_base.hpp"
#include "objects/gui/image.hpp"
#include "objects/gui/button.hpp"
#include "game/level.hpp"
#include "resources.hpp"
#include "scene.hpp"

namespace pftd
{

class GameScene final : public Scene
{
public:
    // TODO: seperate Inventory class which containes InventoryItem-s
    // struct InventoryItem
    // {
    //     gui::Image frame;
    //     gui::Image icon;

    //     // ? TODO: should be drawable?
    // };

    GameScene();
    ~GameScene();

    void onEvent(sf::Event const& ev) override;
    void update(float dt) override;
    bool setActive(bool) override;
    void startGame();

private:
    gui::Image m_mapBackground;
    gui::Image m_inventoryBackground;
    gui::Button m_saveButt;
    sf::Sound m_hornSound = sf::Sound{ResourceManager::getInstance()->getSound("res/audio/ready_for_battle.mp3")};
    sf::Sound m_gameoverSound = sf::Sound{ResourceManager::getInstance()->getSound("res/audio/gameover.mp3")};
    std::vector<std::pair<gui::Image, gui::Image>> m_inventoryItems;

    Level* m_level = nullptr;

};

}