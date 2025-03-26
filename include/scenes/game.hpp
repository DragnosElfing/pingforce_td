#pragma once

#include <utility>
#include <vector>

#include "SFML/Graphics/RenderStates.hpp"
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

    struct InventoryItem : public Object, public Clickable
    {
        gui::Image frame;
        gui::Image icon;

        InventoryItem(std::string const& frameImageSrc, std::string const& iconSrc);
        ~InventoryItem() = default;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

    struct Inventory final : public Object
    {
        std::vector<InventoryItem*> items;
        gui::Image background;
        
        Inventory(std::string const& backgroundImageSrc);
        ~Inventory() = default;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

    GameScene();
    ~GameScene();

    void onEvent(sf::Event const& ev) override;
    void update(float dt) override;
    bool setActive(bool isActive) override;
    void startGame();

private:
    gui::Image m_mapBackground;
    gui::Button m_saveButt;
    sf::Sound m_hornSound = sf::Sound{ResourceManager::getInstance()->getSound("res/audio/ready_for_battle.mp3")};
    sf::Sound m_gameoverSound = sf::Sound{ResourceManager::getInstance()->getSound("res/audio/gameover.mp3")};
    Inventory m_inventory;

    Level* m_level = nullptr;

};

}