#pragma once

#include "objects/gui/mock_image.hpp"
#include "objects/gui/mock_button.hpp"
#include "utils/hetero_collection.hpp"
#include "game/mock_level.hpp"
#include "mock_scene.hpp"

namespace pftd_test
{

using namespace pftd;

/*! Játék nézet tesztelésre szánt változata. */
class GameScene final : public Scene
{
public:
    struct InventoryItem : public Clickable
    {
        gr::Sprite frame;
        gr::Sprite icon;
        Tower* towerToSpawn = nullptr;
        gr::Label priceLabel;

        InventoryItem(Tower* tower, Level * const level, std::string const& iconSrc, 
            utils::Vec2f const& position, utils::Vec2f const& size);
        ~InventoryItem();

        virtual void draw() const;
    };

    struct Inventory final : public Object, public utils::Container<InventoryItem>
    {
        gr::Sprite background;
        
        Inventory(std::string const& backgroundImageSrc);
        ~Inventory() = default;

        void draw() const override;
    };

    GameScene();
    ~GameScene();

    void onEvent(int event) override;
    void update(float dt) override;
    bool toggleActive(bool isActive) override;
    void startGame();
    void updateScore();
    void updateWealth();

//private:
    gr::Button* m_saveButt = nullptr;
    gr::Label* m_moneyCounter = nullptr;
    gr::Label* m_scoreCounter = nullptr;
    Inventory* m_inventory = nullptr;
    Level* m_level = nullptr;

};

}