#pragma once

#ifndef CPORTA

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
    * @param label Szöveg.
    * @param font Betűtípus.
    * @param cSize Betűméret.
    * @param color Betűszín.
    */
    Label(std::wstring const& label, sf::Font const& font, unsigned int cSize, sf::Color const& color = sf::Color::White);

    /**
    * @brief
    *
    * @param label Szöveg.
    * @param font Betűtípus.
    * @param cSize Betűméret.
    * @param position Pozíció.
    * @param zIndex Z koordináta.
    * @param color Betűszín.
    */
    Label(std::wstring const& label, sf::Font const& font, unsigned int cSize, utils::Vec2f position, int zIndex = 0, sf::Color const& color = sf::Color::White);

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

#endif
