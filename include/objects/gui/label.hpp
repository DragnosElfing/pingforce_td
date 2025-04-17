#pragma once

#include "all.hpp"

#include "objects/object_base.hpp"

namespace pftd {
namespace gr {

/*! Felirat GUI elem. */
class Label final : public Object
{
public:
    /**
    * @brief
    *
    * @param text Szöveg objektum: maga a szöveg, betűtípus és betűméret.
    * @param color Betűszín.
    */
    Label(sf::Text const& text, sf::Color const& color = sf::Color::White);

    /**
    * @brief
    *
    * @param text Szöveg objektum: maga a szöveg, betűtípus és betűméret.
    * @param position Pozíció.
    * @param zIndex Z koordináta.
    * @param color Betűszín.
    */
    Label(sf::Text const& text, utils::Vec2f position, int zIndex = 0, sf::Color const& color = sf::Color::White);

    // Ezek mind inline-ok. VVV

    /**
    * @brief Új szöveg beállítása.
    *
    * @param newLabel Az új szöveg.
    */
    void setLabel(std::string const& newLabel) { m_text.setString(newLabel); }

    /**
    * @brief Szöveg outline beállítása.
    *
    * @param color Színe.
    * @param thickness Vastagsága.
    */
    void setOutline(sf::Color color, float thickness = 1.0f) { m_text.setOutlineColor(color); m_text.setOutlineThickness(thickness); }

    /**
    * @brief `m_text` getter.
    *
    * @return A tárolt szöveg objektum.
    */
    sf::Text& getText() { return m_text; }

    /**
    * @brief Konstans `m_text` getter.
    *
    * @return A tárolt szöveg objektum.
    */
    sf::Text const& getText() const { return m_text; }

    /**
    * @brief Objektum megjelenítése.
    *
    * @param target Hol legyen megjelenítve? Ez általában egy ablak.
    * @param states Render-eléshez szükséges egyéb állapotok.
    */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(m_text, states);
    }

private:
    /*! Tárolt szöveg objektum. */
    sf::Text m_text;

};

}
}