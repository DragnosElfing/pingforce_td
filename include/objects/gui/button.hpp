#pragma once

#include <functional>

#include "SFML/Audio/Sound.hpp"
#include "SFML/Graphics.hpp"
#include "objects/gui/image.hpp"
#include "objects/object_base.hpp"
#include "resources.hpp"

namespace pftd {
namespace gui {

// TODO: should inherit a clickable interface
class Button : public Object
{
public:
    bool isActive;

    //template<typename CallbackF>
    // TODO: take in position and size instead of a rect
    Button(sf::Text&&, sf::FloatRect&&, bool active = true, int yIndex = 0);

    virtual ~Button();

    // template<typename CallbackF>
    void setCallback(std::function<void()>);
    void setSound(std::string const&);
    void setBackground(std::string const&);

    std::string getLabel() const { return static_cast<std::string>(m_label.getString()); };

    virtual void handleClick(sf::Vector2i const&);

    virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

private:
    sf::Text m_label;
    sf::FloatRect m_rect;
    Image* m_background = nullptr;
    std::function<void()> m_callback;
    sf::Sound m_clickSound;
    
};

}
}