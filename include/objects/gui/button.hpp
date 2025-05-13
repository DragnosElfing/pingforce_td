#pragma once

#ifndef CPORTA

#include "all.hpp"

#include "objects/clickable.hpp"
#include "objects/gui/image.hpp"
#include "objects/gui/label.hpp"

namespace pftd {
namespace gr {

/*! Gomb GUI elem. */
class Button : public Clickable
{
public:
    /**
    * @brief
    *
    * @param label Szöveg objektum: maga a szöveg, betűtípus és betűméret.
    * @param position Pozíció.
    * @param size Méret.
    * @param active Aktív e? Rá lehet e kattintani.
    * @param zIndex Z koordináta.
    */
    Button(gr::Label const& label, utils::Vec2f const& position, utils::Vec2f const& size, bool active = true, int zIndex = 0);
    virtual ~Button();

    /**
    * @brief Kattintás hangeffekt beállítása.
    *
    * @param src Hangfájl elérési útvonala.
    */
    void setSound(std::string const& src);

    /**
    * @brief Háttérkép beállítása.
    *
    * @param src Háttárkép elérési útvonala.
    */
    void setBackground(std::string const& src);

    /**
    * @brief Ráírt szöveg.
    *
    * @return A tárolt címkére írt szöveg.
    */
    std::string getLabel() const { return static_cast<std::string>(label.getText().getString()); };

    virtual void handleClick(utils::Vec2i const& clickCoords) override;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
    /*! Címke. */
    Label label;

private:
    /*! Minden gomb egy téglalap: ennek a pozíciója és mérete. */
    sf::FloatRect m_rect;

    /*! Háttér. */
    Sprite* m_background = nullptr;

    /*! Kattintás hangeffekt. */
    sf::Sound m_clickSound;

};

}
}

#endif
