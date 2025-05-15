#include "mock_objects/mock_gui/button.hpp"
#include "mock/rman.hpp"

using namespace pftd_test::gr;

Button::Button(gr::Label const& label, utils::Vec2f const& position, utils::Vec2f const& size, bool active, int zIndex):
    Clickable{position, size, zIndex, active},

    label{label}
{

}

Button::~Button()
{
    if(m_background) delete m_background;
}

void Button::setSound(std::string const& source)
{
    ResourceManager::getInstance()->getSound(source);
}

void Button::setBackground(std::string const& id)
{
    if(m_background) delete m_background;
    m_background = new Sprite{ResourceManager::getInstance()->getTexture(id),
        this->position, this->size, this->zIndex};
}

void Button::handleClick(utils::Vec2i const& clickCoords)
{
    Clickable::handleClick(clickCoords);
}

void Button::draw() const
{
    where();
}
