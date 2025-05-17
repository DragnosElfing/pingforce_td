#ifndef CPORTA

#include "SFML/Window/Keyboard.hpp"
#include "objects/entities/towers/iciclestabber.hpp"
#include "objects/entities/towers/snowballer.hpp"
#include "objects/gui/image.hpp"
#include "objects/object_base.hpp"
#include "resources.hpp"
#include "scene.hpp"
#include "scenes/menu.hpp"
#include "scenes/game.hpp"
#include "app.hpp"

#define WIN_WIDTH static_cast<float>(App::getInstance()->getWindowWidth())
#define WIN_HEIGHT static_cast<float>(App::getInstance()->getWindowHeight())

using namespace pftd;

/// Menu
MenuScene::MenuScene()
{
    // Logó
    objects.push_back(new gr::Sprite{"res/images/logo.png", {50, WIN_HEIGHT/2.f - 360}, {620, 620}});

    // Háttérkép
    auto background = new gr::Sprite{"res/images/menu_bg.jpeg", {0, 0},
        {WIN_WIDTH, WIN_HEIGHT}, -100};
    background->modColor({230, 230, 255, 180});
    objects.push_back(background);

    // Le a kalappal!
    objects.push_back(new gr::Label{
        L"A felhasznált illusztrációkat Illés Dóra készítette.", ResourceManager::getInstance()->getDefaultFont(), 16,
        {10, WIN_HEIGHT - 20}
    });

    /* Gombok */
    // Új játék
    auto newGameButt = new gr::Button{{L"Új játék", ResourceManager::getInstance()->getDefaultFont(), 34},
        {WIN_WIDTH - 400.0f, WIN_HEIGHT/2.f - 60},
            {330, 110}};
    newGameButt->setBackground("./res/images/button_bg.png");
    newGameButt->setCallback([&self = newGameButt](){
        App::getInstance()->changeScene("game");
    });
    m_buttons.push_back(newGameButt);

    // Mentett betöltése

    auto loadGameButt = new gr::Button{{L"Mentett betöltése", ResourceManager::getInstance()->getDefaultFont(), 34},
        {WIN_WIDTH - 400.0f, WIN_HEIGHT/2.f + 60},
            {330, 110}, this->_isSaveFileAvailable()};
    loadGameButt->setBackground("./res/images/button_bg.png");
    loadGameButt->setCallback([&self = loadGameButt](){
        App::getInstance()->changeScene("game", Scene::StateFlag::LOAD_STATE);
    });
    m_buttons.push_back(loadGameButt);

    for(auto const& button : m_buttons) {
        objects.push_back(button);
    }

    // Zene
    this->setMusic("res/audio/menu_theme.mp3", 70);
}

void MenuScene::onEvent(sf::Event const& ev)
{
    auto clickEvent = ev.getIf<sf::Event::MouseButtonPressed>();
    if(clickEvent) {
        auto const clickPos = utils::Vec2i{clickEvent->position.x, clickEvent->position.y};
        for(auto const& button : m_buttons) {
            button->handleClick(clickPos);
        }
    }
}

void MenuScene::update(float)
{

}

bool MenuScene::_isSaveFileAvailable()
{
    std::ifstream saveFile {GameScene::SAVE_FILE_PATH};
    bool isAvailable = saveFile.good();
    saveFile.close();

    return isAvailable;
}

void MenuScene::toggleActive(Scene::StateFlag)
{
    Scene::toggleActive();

    if(isActive) {
        m_buttons.at(1)->isActive = this->_isSaveFileAvailable();
    }

}
///

/// InventoryItem
GameScene::InventoryItem::InventoryItem(Tower* tower, Level * const level, utils::Vec2f const& position, utils::Vec2f const& size):
    Clickable{position, size, 100},

    frame{"res/images/inventory_frame.png", position, size},
    icon{tower->getSpriteSheet(), {{0, 0}, {1024, 1024}}, position, size, 100},
    towerToSpawn{tower},
    priceLabel{L"$" + std::to_wstring(towerToSpawn->properties.price), ResourceManager::getInstance()->getDefaultFont(), 21,
        {}, 100, sf::Color::Green}
{
    // Közép-lentre igazítás
    priceLabel.getText().setOrigin(priceLabel.getText().getGlobalBounds().size / 2.0f + priceLabel.getText().getLocalBounds().position);
    priceLabel.getText().setPosition({position.x + size.x / 2.0f, position.y + size.y});

    priceLabel.setOutline(sf::Color::White, 2.5f);

    this->setCallback([this, level](){
        if(!level) return;
        level->selectTower(towerToSpawn->clone());
    });
}

GameScene::InventoryItem::~InventoryItem()
{
    if(towerToSpawn) delete towerToSpawn;
}

void GameScene::InventoryItem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    frame.draw(target, states);
    icon.draw(target, states);
    priceLabel.draw(target, states);
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

void GameScene::Inventory::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    background.draw(target, states);
    for(auto const& item : this->getContainer()) {
        item->draw(target, states);
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
    objects.push_back(new gr::Sprite{"res/images/map.png", {0, 0}, {WIN_WIDTH - 180, WIN_HEIGHT}, -100});

    // Mentés & kilépés gomb
    m_saveButt = new gr::Button{{L"Mentés & Kilépés", ResourceManager::getInstance()->getDefaultFont(), 18},
        {10,10},{180, 60}, true, 100};
    m_saveButt->setBackground("./res/images/button_bg.png");
    m_saveButt->setCallback([&self = m_saveButt, this](){
        m_hornSound.stop();
        m_level->save();
        App::getInstance()->changeScene("menu");
    });
    objects.push_back(m_saveButt);

    // Pénz & pont mutatók
    m_moneyCounter = new gr::Label{
        L"$0", ResourceManager::getInstance()->getDefaultFont(), 24,
        {200, 40}, 100, sf::Color::Green};
    m_scoreCounter = new gr::Label{
        L"Pont: 0", ResourceManager::getInstance()->getDefaultFont(), 24,
        {200, 10}, 100, sf::Color::Cyan};
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

void GameScene::onEvent(sf::Event const& ev)
{
    auto clickEvent = ev.getIf<sf::Event::MouseButtonPressed>();
    if(clickEvent) {
        auto const clickPos = utils::Vec2i{clickEvent->position.x, clickEvent->position.y};
        m_saveButt->handleClick(clickPos);
        for(auto& item : m_inventory->getContainer()) {
            item->handleClick(clickPos);
        }

        bool inBounds = clickEvent->position.x < WIN_WIDTH - 200;
        if(inBounds) {
            m_level->placeTower();
        }
    }

    auto mouseMoveEvent = ev.getIf<sf::Event::MouseMoved>();
    if(mouseMoveEvent) {
        if(m_level->selectedTower) {
            m_level->selectedTower->setPosition({static_cast<float>(mouseMoveEvent->position.x), static_cast<float>(mouseMoveEvent->position.y)});
        }
    }

    auto keyPressEvent = ev.getIf<sf::Event::KeyPressed>();
    if(keyPressEvent && keyPressEvent->scancode == sf::Keyboard::Scancode::Escape) {
        m_level->deselectTower();
    }
}

void GameScene::update(float dt)
{
    this->updateScore();
    this->updateWealth();

    if(m_level->isGameOver()) {
        backgroundMusic->stop();
        this->m_gameoverSound.play();
        App::getInstance()->changeScene("menu");
    }

    m_level->update(dt);
}

void GameScene::toggleActive(Scene::StateFlag flag)
{
    Scene::toggleActive(flag);

    if(isActive) {
        // Megoldható lenne egyedi operator&-ral.
        if((static_cast<uint8_t>(flag) & static_cast<uint8_t>(Scene::StateFlag::LOAD_STATE)) == static_cast<uint8_t>(Scene::StateFlag::LOAD_STATE)) {
            m_shouldLoadSaved = true;
        }
        this->startGame();
    }

}

void GameScene::_constructInventory()
{
    // Inventory feltöltése
    // Snowballer
    auto snowballerTower = new InventoryItem{new Snowballer{}, m_level, {WIN_WIDTH - 180, 10}, {170, 170}};
    m_inventory->append(snowballerTower);

    // IcicleStabber
    auto icicleTower = new InventoryItem{new IcicleStabber{}, m_level, {WIN_WIDTH - 180, 180+10+10}, {170, 170}};
    m_inventory->append(icicleTower);

    m_hornSound.play();
    m_hornSound.setVolume(100);
}

void GameScene::startGame()
{
    if(m_shouldLoadSaved) {
        m_level->loadFromSave();
        m_shouldLoadSaved = false;
    } else {
        m_level->reset();
    }

    this->_constructInventory();
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

#endif
