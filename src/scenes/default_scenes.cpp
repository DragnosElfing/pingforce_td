#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"
#include "objects/entities/towers/iciclestabber.hpp"
#include "objects/entities/towers/snowballer.hpp"
#include "objects/gui/image.hpp"
#include "objects/object_base.hpp"
#include "resources.hpp"
#include "scene.hpp"
#include "scenes/menu.hpp"
#include "scenes/game.hpp"
#include "utils/logger.hpp"
#include "app.hpp"

#define WIN_WIDTH static_cast<float>(App::getInstance()->getWindowWidth())
#define WIN_HEIGHT static_cast<float>(App::getInstance()->getWindowHeight())

using namespace pftd;

/// Menu
MenuScene::MenuScene()
{
    // Logó
    objects.push_back(new gr::Sprite{"res/images/logo.png", {50, App::getInstance()->getWindowHeight()/2.f - 360}, {620, 620}});
    
    // Háttérkép
    auto background = new gr::Sprite{"res/images/menu_bg.jpeg", {0, 0}, 
        {WIN_WIDTH, WIN_HEIGHT}, -100};
    background->modColor({230, 230, 255, 180});
    objects.push_back(background);

    // Le a kalappal!
    objects.push_back(new gr::Label{
        sf::Text{ResourceManager::getInstance()->getDefaultFont(), L"A felhasznált illusztrációkat Illés Dóra készítette.", 16}, 
        {10, WIN_HEIGHT - 20}
    });

    /* Gombok */
    // Új játék
    auto newGameButt = new gr::Button{sf::Text{ResourceManager::getInstance()->getDefaultFont(), L"Új játék", 34},
        {WIN_WIDTH - 400.0f, WIN_HEIGHT/2.f - 60}, 
            {330, 110}};
    newGameButt->setBackground("./res/images/button_bg.png");
    newGameButt->setCallback([&self = newGameButt](){
        App::getInstance()->changeScene("game");
    });
    m_buttons.push_back(newGameButt);

    // Mentett betöltése
    // Ellenőrzi, hogy létezik e a save fájl, és, hogy meg lehet e nyitni.
    std::ifstream saveFile {GameScene::SAVE_FILE_PATH};
    bool loadButtonActive = saveFile.good();
    saveFile.close();

    auto loadGameButt = new gr::Button{sf::Text{ResourceManager::getInstance()->getDefaultFont(), L"Mentett betöltése", 34}, 
        {WIN_WIDTH - 400.0f, WIN_HEIGHT/2.f + 60}, 
            {330, 110}, loadButtonActive};
    loadGameButt->setBackground("./res/images/button_bg.png");
    loadGameButt->setCallback([&self = loadGameButt](){ 
        App::getInstance()->changeScene("game", SceneStateFlag::LOAD_STATE);
    });
    m_buttons.push_back(loadGameButt);

    for(auto const& button : m_buttons) {
        objects.push_back(button);
    }

    // Zene
    this->setMusic("res/audio/menu_theme.mp3", 70);
}

MenuScene::~MenuScene()
{

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

void MenuScene::toggleActive(SceneStateFlag)
{
    if(!isActive) {
        std::ifstream saveFile {GameScene::SAVE_FILE_PATH};
        m_buttons[1]->isActive = saveFile.good();
        saveFile.close();
    }

    Scene::toggleActive();
}
///

/// InventoryItem
GameScene::InventoryItem::InventoryItem(Tower* tower, Level * const level, utils::Vec2f const& position, utils::Vec2f const& size):
    Clickable{position, size, 100},

    frame{"res/images/inventory_frame.png", position, size},
    icon{tower->getSpriteSheet(), {{0, 0}, {1024, 1024}}, position, size, 100},
    towerToSpawn{tower},
    priceLabel{{ResourceManager::getInstance()->getDefaultFont(), "$" + std::to_string(towerToSpawn->price), 21}, 
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
        {static_cast<float>(App::getInstance()->getWindowWidth() - 200), 0}, 
        {200, static_cast<float>(App::getInstance()->getWindowHeight())}, 1
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
GameScene::GameScene()
{
    // Háttér
    objects.push_back(new gr::Sprite{"res/images/map.png", {0, 0}, {WIN_WIDTH - 180, WIN_HEIGHT}, -100});
    
    // Mentés & kilépés gomb
    m_saveButt = new gr::Button{sf::Text{ResourceManager::getInstance()->getDefaultFont(), L"Mentés & Kilépés", 18}, 
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
        sf::Text{ResourceManager::getInstance()->getDefaultFont(), L"$0", 24}, 
        {200, 40}, 100, sf::Color::Green};
    m_scoreCounter = new gr::Label{
        sf::Text{ResourceManager::getInstance()->getDefaultFont(), L"Pont: 0", 24}, 
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

        bool inBounds = clickEvent->position.x < App::getInstance()->getWindowWidth() - 200;
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

void GameScene::toggleActive(SceneStateFlag flag)
{
    if(!isActive) {
        // TODO: no
        if((static_cast<uint8_t>(flag) & static_cast<uint8_t>(SceneStateFlag::LOAD_STATE)) == static_cast<uint8_t>(SceneStateFlag::LOAD_STATE)) {
            m_shouldLoadSaved = true;
            where();
        }
        this->startGame();
    }

    Scene::toggleActive(flag);
}

void GameScene::startGame()
{
    //bool firstTime = !m_level;
    if(m_level) {
        // TODO: tényleg ideiglenes jó
        objects.erase(std::remove(objects.begin(), objects.end(), m_level));
        delete m_level;
        m_level = nullptr;
    }

    if(m_shouldLoadSaved) {
        m_level = new Level{GameScene::SAVE_FILE_PATH};
        m_shouldLoadSaved = false;
    } else {
        Level::Stats defStats {3, 3, 0, 250};
        m_level = new Level{GameScene::SAVE_FILE_PATH, defStats};
    }

    if(true) {
        objects.push_back(m_level);
    }

    // Inventory feltöltése
    // TODO: m_inventory should calculate the positions of its items and also define their size
    // Snowballer
    auto snowballerTower = new InventoryItem{new Snowballer{}, m_level, {WIN_WIDTH - 180, 10}, {170, 170}};
    m_inventory->append(snowballerTower);
    
    // IcicleStabber
    auto icicleTower = new InventoryItem{new IcicleStabber{}, m_level, {WIN_WIDTH - 180, 180+10+10}, {170, 170}};
    m_inventory->append(icicleTower);

    m_hornSound.play();
    m_hornSound.setVolume(100);
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
