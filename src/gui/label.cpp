#include "objects/gui/label.hpp"

using namespace pftd::gr;

Label::Label(sf::Text const& text, sf::Color const& color):
    m_text{text}
{
    m_text.setFillColor(color);
}

Label::Label(sf::Text const& text, utils::Vec2f position, int zIndex, sf::Color const& color):
    Object{position, {}, zIndex},
    m_text{text}
{
    m_text.setPosition({position.x, position.y});
    m_text.setFillColor(color);
}