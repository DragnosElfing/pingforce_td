#pragma once

#include "objects/gui/image.hpp"
#include "objects/gui/button.hpp"
#include "utils/hetero_collection.hpp"
#include "game/level.hpp"
#include "resources.hpp"
#include "scene.hpp"

namespace pftd
{

/*! Játék nézet. */
class GameScene final : public Scene
{
public:
    /*! Az "eszköztárban" tárolt torony. */
    struct InventoryItem : public Clickable
    {
        /*! Keret. */
        gr::Sprite frame;

        /*! Ikon. */
        gr::Sprite icon;

        /*! Torony amit meg szeretnénk venni. */
        Tower* towerToSpawn = nullptr;

        /*! Árcímke (felirat). */
        gr::Label priceLabel;

        // TODO: remove iconSrc and textureRect params
        InventoryItem(Tower* tower, Level * const level, std::string const& iconSrc, sf::IntRect const& textureRect, 
            utils::Vec2f const& position, utils::Vec2f const& size);
        ~InventoryItem();

        /**
        * @brief Objektum megjelenítése.
        *
        * @param target Hol legyen megjelenítve? Ez általában egy ablak.
        * @param states Render-eléshez szükséges egyéb állapotok.
        */
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

    /*! "Eszköztár": innen lehet megvenni a tornyokat. */
    struct Inventory final : public Object, public utils::Container<InventoryItem>
    {
        /*! Háttér. */
        gr::Sprite background;
        
        /**
        * @brief
        *
        * @param backgroundImageSrc Háttérkép elérési útvonala.
        */
        Inventory(std::string const& backgroundImageSrc);
        ~Inventory() = default;

        /**
        * @brief Objektum megjelenítése.
        *
        * @param target Hol legyen megjelenítve? Ez általában egy ablak.
        * @param states Render-eléshez szükséges egyéb állapotok.
        */
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

    GameScene();
    ~GameScene();

    /**
    * @brief Delegált események kezelése.
    *
    * @param event Kezelni kívánt esemény.
    */
    void onEvent(sf::Event const& event) override;

    /**
    * @brief Update.
    *
    * @param dt Delta idő.
    */
    void update(float dt) override;

    /**
    * @brief Nézet aktiválása/deaktiválása.
    *
    * @param isActive Aktiválás e?
    * @return Történt e állapot változás.
    */
    bool toggleActive(bool isActive) override;

    /**
    * @brief Játék elindítása.
    *
    * Inicializálja a játék kezdetét: létrehozza a "szintet."
    */
    void startGame();

    /**
    * @brief Pontszám felirat frissítése.
    */
    void updateScore();

    /**
    * @brief Pénz felirat frissítése.
    */
    void updateWealth();

private:
    //gr::Sprite* m_mapBackground = nullptr;

    /*! Mentés gomb. */
    gr::Button* m_saveButt = nullptr;

    /*! Pánzszámláló felirat. */
    gr::Label* m_moneyCounter = nullptr;

    /*! Pontszámláló felirat. */
    gr::Label* m_scoreCounter = nullptr;

    /*! Kürt hang. Ez a játék elindításánál játszódik be. */
    sf::Sound m_hornSound = sf::Sound{ResourceManager::getInstance()->getSound("res/audio/ready_for_battle.mp3")};

    /*! Játék vége hangeffekt. */
    sf::Sound m_gameoverSound = sf::Sound{ResourceManager::getInstance()->getSound("res/audio/gameover.mp3")};

    /*! Az "eszköztár." */
    Inventory* m_inventory = nullptr;

    /*! Játéklogikát tartalmazó "szint."*/
    Level* m_level = nullptr;

};

}