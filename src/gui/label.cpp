#ifndef CPORTA

#include "objects/gui/label.hpp"

using namespace pftd::gr;

Label::Label(std::wstring const& label, sf::Font const& font, unsigned int cSize, sf::Color const& color):
    m_text{sf::Text{font, label, cSize}}
{
    m_text.setFillColor(color);
}

Label::Label(std::wstring const& label, sf::Font const& font, unsigned int cSize, utils::Vec2f position, int zIndex, sf::Color const& color):
    Object{position, {}, zIndex},
    m_text{sf::Text{font, label, cSize}}
{
    m_text.setPosition({position.x, position.y});
    m_text.setFillColor(color);
}

#endif
