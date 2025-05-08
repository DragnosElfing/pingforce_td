#pragma once

#include "all.hpp"

#include "objects/mock_object_base.hpp"

namespace pftd_test 
{
namespace gr 
{

using namespace pftd;

/*! Teszteléshez szánt Sprite. */
class Sprite final : public Object
{
public:
    Sprite(std::string const& imageSrc, utils::Vec2f const& position, utils::Vec2f const& size, int zIndex = -1);
    Sprite(Sprite const& other);
    Sprite(Sprite&& other) noexcept;
    ~Sprite() = default;

    void modColor(uint8_t color);
    void setSpriteRect(utils::Vec2i const& textureRectStart, utils::Vec2i const& textureRectEnd);
    void draw() const override;

};

}
}