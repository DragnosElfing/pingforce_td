#include <cmath>
#include <ctime>

#include "SFML/Audio/Sound.hpp"
#include "SFML/System/Angle.hpp"

#include "objects/gui/image.hpp"
#include "resources.hpp"
#include "scene.hpp"
#include "scenes/menu.hpp"
#include "scenes/game.hpp"
#include "utils/logger.hpp"
#include "app.hpp"

using namespace pftd;

/// Menu
MenuScene::MenuScene():
    m_logo{"res/images/logo.png", 
        {50, App::getInstance()->getWindowHeight()/2 - 360}, 
        {620, 620}},

    m_background{"res/images/menu_bg.jpeg", 
        {0, 0}, 
        {App::getInstance()->getWindowWidth(), App::getInstance()->getWindowHeight()}, -100},

    m_newGameButt{sf::Text{ResourceManager::getInstance()->defaultFont, L"Új játék", 34}, 
        sf::FloatRect{
            {App::getInstance()->getWindowWidth() - 400.0f, App::getInstance()->getWindowHeight()/2.f - 60}, 
            {330, 110}}},
        
    m_loadGameButt{sf::Text{ResourceManager::getInstance()->defaultFont, L"Mentett betöltése", 34}, 
        sf::FloatRect{
            {App::getInstance()->getWindowWidth() - 400.0f, App::getInstance()->getWindowHeight()/2.f + 60}, 
            {330, 110}}, false}
{
    m_background.modColor({230, 230, 255, 180});

    m_newGameButt.setBackground("./res/images/button_bg.png");
    m_newGameButt.setCallback([&self = m_newGameButt](){
        App::getInstance()->changeScene("game");
    });
    
    m_loadGameButt.setBackground("./res/images/button_bg.png");
    m_loadGameButt.setCallback([&self = m_loadGameButt](){ 
        // TODO
    });

    objects.push_back(&m_newGameButt);
    objects.push_back(&m_loadGameButt);
    objects.push_back(&m_background);
    objects.push_back(&m_logo);

    this->setMusic("res/audio/menu_theme.mp3");
    backgroundMusic->setVolume(70);
}

MenuScene::~MenuScene()
{

}

void MenuScene::onEvent(sf::Event const& ev)
{   
    auto clickEvent = ev.getIf<sf::Event::MouseButtonPressed>();
    if(clickEvent) {
        auto const& clickPos = clickEvent->position;
        m_newGameButt.handleClick(clickPos.x, clickPos.y);
        m_loadGameButt.handleClick(clickPos.x, clickPos.y);
    }
}

void MenuScene::update(float)
{

}
///

/// InventoryItem

///

/// Inventory

///

/// Game
GameScene::GameScene():
    m_mapBackground{"res/images/map.png", 
        {0, 0}, {App::getInstance()->getWindowWidth() - 180, App::getInstance()->getWindowHeight()}, -100},

    m_inventoryBackground{"res/images/inventory.png", 
        {App::getInstance()->getWindowWidth() - 200, 0}, {200, App::getInstance()->getWindowHeight()}, 1},

    m_saveButt{sf::Text{ResourceManager::getInstance()->defaultFont, L"Mentés & Kilépés", 18}, 
        sf::FloatRect{{10,10},{180, 60}}, true, 100}
{
    m_saveButt.setBackground("./res/images/button_bg.png");
    m_saveButt.setCallback([&self = m_saveButt, this](){ 
        App::getInstance()->changeScene("menu");
    });

    objects.push_back(&m_mapBackground);
    objects.push_back(&m_inventoryBackground);
    objects.push_back(&m_saveButt);

    this->setMusic("res/audio/defend.mp3");
    backgroundMusic->setVolume(90);

    // TODO: no
    m_inventoryItems.emplace_back(
        gui::Image{ResourceManager::getInstance()->getTexture("res/images/inventory_frame.png"), 
            {App::getInstance()->getWindowWidth() - 180, 10}, {170, 170}, 99
        },
        gui::Image{ResourceManager::getInstance()->getTexture("res/images/penguins/snowballer_peng.png"), {{0, 0}, {1024, 1024}},
            {App::getInstance()->getWindowWidth() - 180, 10}, {170, 170}, 100
        }
    );

    m_inventoryItems.emplace_back(
        gui::Image{ResourceManager::getInstance()->getTexture("res/images/inventory_frame.png"), 
            {App::getInstance()->getWindowWidth() - 180, 180+10+10}, {170, 170}, 99
        },
        gui::Image{ResourceManager::getInstance()->getTexture("res/images/penguins/iciclestabber_peng.png"), {{0, 0}, {1024, 1024}},
            {App::getInstance()->getWindowWidth() - 180, 180+10+10}, {170, 170}, 100
        }
    );

    for(auto& item : m_inventoryItems) {
        objects.push_back(&item.first);
        objects.push_back(&item.second);
    }
}

GameScene::~GameScene()
{
    
}

void GameScene::onEvent(sf::Event const& ev)
{
    auto clickEvent = ev.getIf<sf::Event::MouseButtonPressed>();
    if(clickEvent) {
        m_saveButt.handleClick(clickEvent->position.x, clickEvent->position.y);
    }

    // TODO: move this into update
    if(m_level->isGameOver()) {
        backgroundMusic->stop();
        this->m_gameoverSound.play();
    }
}

void GameScene::update(float)
{
    
}

bool GameScene::setActive(bool active) 
{
    if(active) {
        this->startGame();
    } else {
        m_hornSound.stop();
    }

    return Scene::setActive(active);
}

void GameScene::startGame()
{
    if(m_level) delete m_level;

    m_level = new Level{
        Level::Nest{ResourceManager::getInstance()->getTexture("res/images/eggs.png"), 1020, 500}
    };
    // TODO: seperate config file
    m_level->followPath.path.push_back({-100, 155});
    m_level->followPath.path.push_back({500, 155});
    m_level->followPath.path.push_back({490, 310});
    m_level->followPath.path.push_back({135, 300});
    m_level->followPath.path.push_back({80, 380});
    m_level->followPath.path.push_back({90, 470});
    m_level->followPath.path.push_back({120, 550});
    m_level->followPath.path.push_back({490, 550});
    m_level->followPath.path.push_back({500, 700});
    m_level->followPath.path.push_back({620, 715});
    m_level->followPath.path.push_back({660, 390});
    m_level->followPath.path.push_back({645, 135});
    m_level->followPath.path.push_back({885, 105});
    m_level->followPath.path.push_back({1095, 130});
    m_level->followPath.path.push_back({1070, 395});
    m_level->followPath.path.push_back({855, 390});
    m_level->followPath.path.push_back({845, 605});
    m_level->followPath.path.push_back({1055, 615});

    objects.push_back(&m_level->nest.sprite);
    objects.push_back(&m_level->followPath);

    m_hornSound.play();
    m_hornSound.setVolume(100);
}

///
