#pragma once

#include "objects/gui/image.hpp"
#include "objects/gui/button.hpp"
#include "utils/hetero_collection.hpp"
#include "game/level.hpp"
#include "resources.hpp"
#include "scene.hpp"

namespace pftd
{

class GameScene final : public Scene
{
public:
    struct InventoryItem : public Clickable
    {
        gr::Sprite frame;
        gr::Sprite icon;
        Tower* towerToSpawn = nullptr;
        gr::Label priceLabel;

        // TODO: remove iconSrc and textureRect params
        InventoryItem(Tower* tower, Level * const level, std::string const& iconSrc, sf::IntRect const& textureRect, 
            utils::Vec2f const& position, utils::Vec2f const& size);
        ~InventoryItem() = default; // ? delete own tower? YES! Maybe...
        
        //virtual void handleClick(int x, int y) override;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

    struct Inventory final : public Object, public utils::HCollection<InventoryItem*>
    {
        gr::Sprite background;
        
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
    void updateScore();
    void updateWealth();

private:
    //gr::Sprite* m_mapBackground = nullptr;
    gr::Button* m_saveButt = nullptr;
    gr::Label* m_moneyCounter = nullptr;
    gr::Label* m_scoreCounter = nullptr;
    sf::Sound m_hornSound = sf::Sound{ResourceManager::getInstance()->getSound("res/audio/ready_for_battle.mp3")};
    sf::Sound m_gameoverSound = sf::Sound{ResourceManager::getInstance()->getSound("res/audio/gameover.mp3")};
    Inventory* m_inventory = nullptr;

    Level* m_level = nullptr;

};

}