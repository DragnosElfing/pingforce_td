#pragma once

#include <functional>

#include "SFML/Audio/Sound.hpp"
#include "SFML/Graphics.hpp"

#include "objects/clickable.hpp"
#include "objects/gui/image.hpp"
#include "objects/gui/label.hpp"
#include "objects/object_base.hpp"
#include "utils/substitute_types.hpp"
#include "resources.hpp"

namespace pftd {
namespace gr {

class Button : public Clickable
{
public:
    Button(sf::Text&& label, utils::Vec2f const& position, utils::Vec2f const& size, bool active = true, int zIndex = 0);
    virtual ~Button();

    //virtual void setCallback(std::function<void()> callback) override;
    void setSound(std::string const& src);
    void setBackground(std::string const& src);

    std::string getLabel() const { return static_cast<std::string>(m_label.getText().getString()); };
    virtual void handleClick(int x, int y) override;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    Label m_label;
    sf::FloatRect m_rect;
    Sprite* m_background = nullptr;
    sf::Sound m_clickSound;
    
};

}
}