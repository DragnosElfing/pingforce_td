#pragma once

#include "all.hpp"

#include "mock_objects/object_base.hpp"

namespace pftd_test {
namespace gr {

using namespace pftd;

/*! Teszteléshez szánt Sprite. */
class Sprite final : public Object
{
public:
    Sprite(int texture, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex);
    Sprite(std::string const& imageSrc, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex = -1);
    Sprite(Sprite const& other);
    Sprite(Sprite&& other) noexcept;
    ~Sprite() = default;

    void scale(utils::Vec2f const& factor);
    void modColor(uint32_t color);
    void setPosition(utils::Vec2f const&) { where(); }
    void setSpriteRect(utils::Vec2i const&, utils::Vec2i const&) { where(); };
    void draw() const override;

};

}
}
