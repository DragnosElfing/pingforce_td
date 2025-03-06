#include "SFML/Graphics/Rect.hpp"

#include "resources.hpp"
#include "scene.hpp"
#include "scenes/menu.hpp"
#include "scenes/game.hpp"
#include "utils/logger.hpp"
#include "app.hpp"

using namespace pftd;

/// Menu
MenuScene::MenuScene(ResourceManager& rman): 
    Scene{rman},
    m_newGameButt{sf::Text{rman.defaultFont, "New Game"}, 
        sf::FloatRect{{10,10},{200, 80}}}
{
    where();

    m_newGameButt.setCallback([this](){ 
        print("CLICKED: " << m_newGameButt.getLabel());
        App::getInstance()->changeScene("game");
    });
    objects.push_back(&m_newGameButt);
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
    }
}
///

/// Game
GameScene::GameScene(ResourceManager& rman): 
    Scene{rman}
{
    where();
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