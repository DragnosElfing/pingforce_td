#include "resources.hpp"
#include "scene.hpp"
#include "scenes/menu.hpp"
#include "scenes/game.hpp"
#include "utils/logger.hpp"
#include "app.hpp"

using namespace pftd;

/// Menu
MenuScene::MenuScene():
    m_logo{"res/images/logo.png", {App::getInstance()->getWindowWidth()/2 - 480, App::getInstance()->getWindowHeight()/2 - 280}, {960, 400}},
    m_background{"res/images/menu_bg.jpeg", {0, 0}, {App::getInstance()->getWindowWidth(), App::getInstance()->getWindowHeight()}, -100},
    m_newGameButt{sf::Text{ResourceManager::getInstance()->defaultFont, L"Új játék"}, 
        sf::FloatRect{{720 - 150,500},{300, 50}}},
    m_loadGameButt{sf::Text{ResourceManager::getInstance()->defaultFont, L"Mentett betöltése"}, 
        sf::FloatRect{{720 - 150,580},{300, 50}}, false}
{
    where();

    m_background.modColor({230, 230, 255, 180});

    m_newGameButt.setCallback([&self = m_newGameButt](){ 
        App::getInstance()->changeScene("game");
        print("CLICKED: " << self.getLabel());
    });
    
    m_loadGameButt.setCallback([&self = m_loadGameButt](){ 
        print("CLICKED: " << self.getLabel());
    });

    objects.push_back(&m_newGameButt);
    objects.push_back(&m_loadGameButt);
    objects.push_back(&m_background);
    objects.push_back(&m_logo);
}

MenuScene::~MenuScene()
{
    where();
}

void MenuScene::onEvent(sf::Event const& ev)
{
    where();
    
    auto clickEvent = ev.getIf<sf::Event::MouseButtonPressed>();
    if(clickEvent) {
        m_newGameButt.handleClick(clickEvent->position);
        m_loadGameButt.handleClick(clickEvent->position);
    }
}
///

/// Game
GameScene::GameScene():
    m_testImage{"res/images/penguins/snowballer_peng.png", {10, 10}, {300, 300}}
{
    where();

    objects.push_back(&m_testImage);
}

GameScene::~GameScene()
{
    where();
}

void GameScene::onEvent(sf::Event const& ev)
{
    where();
    print(ev.is<sf::Event::MouseButtonPressed>());
}
///