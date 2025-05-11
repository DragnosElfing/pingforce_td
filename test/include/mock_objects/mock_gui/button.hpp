#pragma once

#include "all.hpp"

#include "mock_objects/clickable.hpp"
#include "mock_objects/mock_gui/image.hpp"
#include "mock_objects/mock_gui/label.hpp"
#include "mock_objects/object_base.hpp"

namespace pftd_test 
{
namespace gr 
{

using namespace pftd;

/*! Tesztelésre használt gomb. */
class Button : public Clickable
{
public:
    Button(std::string const& label, utils::Vec2f const& position, utils::Vec2f const& size, bool active = true, int zIndex = 0);
    virtual ~Button();

    void setSound(std::string const& src);
    void setBackground(std::string const& src);
    std::string getLabel() const { return static_cast<std::string>(label.getText()); };
    virtual void handleClick(utils::Vec2i const& clickCoords) override;
    virtual void draw() const override;

protected:
    Label label;

private:
    //sf::FloatRect m_rect;
    Sprite* m_background = nullptr;
    
};

}
}