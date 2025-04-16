#pragma once

#include "all.hpp"

#include "objects/object_base.hpp"

namespace pftd {
namespace gr {

class Label final : public Object
{
public:
    Label(sf::Text const& text, sf::Color const& color = sf::Color::White):
        m_text{text}
    {
        m_text.setFillColor(color);
    }
    Label(sf::Text const& text, utils::Vec2f position, int zIndex = 0, sf::Color const& color = sf::Color::White):
        Object{position, {}, zIndex},
        m_text{text}
    {
        m_text.setPosition({position.x, position.y});
        m_text.setFillColor(color);
    }

    void setLabel(std::string const& newLabel) { m_text.setString(newLabel); }
    void setOutline(sf::Color color, float thickness = 1.0f) { m_text.setOutlineColor(color); m_text.setOutlineThickness(thickness); }
    sf::Text& getText() { return m_text; }
    sf::Text const& getText() const { return m_text; }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(m_text, states);
    }

private:
    sf::Text m_text;

};

}
}