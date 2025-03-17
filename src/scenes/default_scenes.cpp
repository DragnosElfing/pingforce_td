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

    m_newGameButt.setBackground("button_bg");
    m_newGameButt.setCallback([&self = m_newGameButt](){ 
        App::getInstance()->changeScene("game");
    });
    
    m_loadGameButt.setBackground("button_bg");
    m_loadGameButt.setCallback([&self = m_loadGameButt](){ 
        // TODO
    });

    objects.push_back(&m_newGameButt);
    objects.push_back(&m_loadGameButt);
    objects.push_back(&m_background);
    objects.push_back(&m_logo);
}

MenuScene::~MenuScene()
{

}

void MenuScene::onEvent(sf::Event const& ev)
{   
    auto clickEvent = ev.getIf<sf::Event::MouseButtonPressed>();
    if(clickEvent) {
        m_newGameButt.handleClick(clickEvent->position);
        m_loadGameButt.handleClick(clickEvent->position);
    }
}
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
    m_saveButt.setBackground("button_bg");
    m_saveButt.setCallback([&self = m_saveButt](){ 
        App::getInstance()->changeScene("menu");
    });

    objects.push_back(&m_mapBackground);
    objects.push_back(&m_inventoryBackground);
    objects.push_back(&m_saveButt);
}

GameScene::~GameScene()
{

}

void GameScene::onEvent(sf::Event const& ev)
{
    auto clickEvent = ev.getIf<sf::Event::MouseButtonPressed>();
    if(clickEvent) {
        m_saveButt.handleClick(clickEvent->position);
    }
}
///
