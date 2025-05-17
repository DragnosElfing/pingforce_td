#include "mock/app.hpp"
#include "mock/rman.hpp"
#include "mock_scenes/game.hpp"
#include "mock_scenes/menu.hpp"
#include "mock_objects/mock_gui/button.hpp"
#include "mock_objects/mock_gui/label.hpp"

#define WIN_WIDTH static_cast<float>(App::getInstance()->getWindowWidth())
#define WIN_HEIGHT static_cast<float>(App::getInstance()->getWindowHeight())

using namespace pftd_test;

/// Menu
MenuScene::MenuScene()
{
    // Logó
    objects.push_back(new gr::Sprite{"test/f/test.png", {50, WIN_HEIGHT/2.f - 360}, {620, 620}});

    // Háttérkép
    auto background = new gr::Sprite{222, {0, 0},
        {WIN_WIDTH, WIN_HEIGHT}, -100};
    background->modColor(0xBEEFEE);
    objects.push_back(background);

    // Le a kalappal!
    objects.push_back(new gr::Label{
        L"A felhasznált illusztrációkat Illés Dóra készítette.", ResourceManager::getInstance()->getDefaultFont(), 16,
        {10, WIN_HEIGHT - 20}
    });

    /* Gombok */
    // Új játék
    auto newGameButt = new gr::Button{{L"Új játék", ResourceManager::getInstance()->getDefaultFont(), 34},
        {0, 0},
            {330, 110}};
    newGameButt->setBackground("./res/images/button_bg.png");
    newGameButt->setCallback([](){
        App::getInstance()->changeScene("game");
    });
    m_buttons.push_back(newGameButt);

    // Mentett betöltése

    auto loadGameButt = new gr::Button{{L"Mentett betöltése", ResourceManager::getInstance()->getDefaultFont(), 34},
        {500, 500},
            {330, 110}, true};
    loadGameButt->setBackground("./res/images/button_bg.png");
    loadGameButt->setCallback([](){
        App::getInstance()->changeScene("game", Scene::StateFlag::LOAD_STATE);
    });
    m_buttons.push_back(loadGameButt);

    for(auto const& button : m_buttons) {
        objects.push_back(button);
    }

    // Zene
    this->setMusic("res/audio/menu_theme.mp3", 70);
}

void MenuScene::onEvent(int)
{
    where();
}

void MenuScene::update(float)
{
    where();
}
///

/// InventoryItem
GameScene::InventoryItem::InventoryItem(Tower* tower, Level * const level, utils::Vec2f const& position, utils::Vec2f const& size):
    Clickable{position, size, 100},

    frame{"test/f/test.png", position, size},
    icon{tower->getSpriteSheet(), position, size, 100},
    towerToSpawn{tower},
    priceLabel{L"$" + std::to_wstring(towerToSpawn->properties.price), ResourceManager::getInstance()->getDefaultFont(), 21,
        {}, 100}
{
    // Közép-lentre igazítás
    // ...

    priceLabel.setOutline(0xBEEFEE, 2.5f);

    this->setCallback([this, level](){
        if(!level) return;
        level->selectTower(towerToSpawn->clone());
    });
}

GameScene::InventoryItem::~InventoryItem()
{
    if(towerToSpawn) delete towerToSpawn;
}

void GameScene::InventoryItem::draw() const
{
    where();
}
///

/// Inventory
GameScene::Inventory::Inventory(std::string const& backgroundImageSrc):
    background{
        ResourceManager::getInstance()->getTexture(backgroundImageSrc),
        {WIN_WIDTH - 200, 0},
        {200, WIN_HEIGHT}, 1
    }
{

}

void GameScene::Inventory::draw() const
{
    background.draw();
    for(auto const& item : this->getContainer()) {
        item->draw();
    }
}
///

/// Game
GameScene::GameScene():
    m_level{new Level{GameScene::SAVE_FILE_PATH}}
{
    // Level
    objects.push_back(m_level);

    // Háttér
    objects.push_back(new gr::Sprite{222, {0, 0}, {WIN_WIDTH - 180, WIN_HEIGHT}, -100});

    // Mentés & kilépés gomb
    m_saveButt = new gr::Button{{L"Mentés & Kilépés", ResourceManager::getInstance()->getDefaultFont(), 18},
        {10,10},{180, 60}, true, 100};
    m_saveButt->setBackground("./res/images/button_bg.png");
    m_saveButt->setCallback([this](){
        m_level->save();
        App::getInstance()->changeScene("menu");
    });
    objects.push_back(m_saveButt);

    // Pénz & pont mutatók
    m_moneyCounter = new gr::Label{
        L"$0", ResourceManager::getInstance()->getDefaultFont(), 24,
        {200, 40}, 100};
    m_scoreCounter = new gr::Label{
        L"Pont: 0", ResourceManager::getInstance()->getDefaultFont(), 24,
        {200, 10}, 100};
    objects.push_back(m_moneyCounter);
    objects.push_back(m_scoreCounter);

    /* Inventory */
    m_inventory = new Inventory{"res/images/inventory.png"};
    objects.push_back(m_inventory);

    // Zene
    this->setMusic("res/audio/defend.mp3", 90);
}

GameScene::~GameScene()
{

}

void GameScene::onEvent(int)
{
    where();
}

void GameScene::update(float dt)
{
    this->updateScore();
    this->updateWealth();

    if(m_level->isGameOver()) {
        App::getInstance()->changeScene("menu");
    }

    m_level->update(dt);
}

bool GameScene::toggleActive(Scene::StateFlag flag)
{
    if(!isActive) {
        // Megoldható lenne egyedi operator&-ral.
        if((static_cast<uint8_t>(flag) & static_cast<uint8_t>(Scene::StateFlag::LOAD_STATE)) == static_cast<uint8_t>(Scene::StateFlag::LOAD_STATE)) {
            m_shouldLoadSaved = true;
        }
        this->startGame();
    }

    return Scene::toggleActive(flag);
}

void GameScene::startGame()
{
    if(m_shouldLoadSaved) {
        m_level->loadFromSave();
        m_shouldLoadSaved = false;
    } else {
        m_level->reset();
    }
}

void GameScene::updateScore()
{
    m_scoreCounter->setLabel(std::to_string(m_level->stats.score));
}

void GameScene::updateWealth()
{
    m_moneyCounter->setLabel("$" + std::to_string(m_level->stats.money));
}

///
