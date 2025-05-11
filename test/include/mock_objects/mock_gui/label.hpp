#pragma once

#include "all.hpp"

#include "mock_objects/object_base.hpp"

namespace pftd_test 
{
namespace gr 
{

using namespace pftd;

/*! Felirat GUI elem. */
class Label final : public Object
{
public:
    Label(std::string const& text, uint32_t color = 0xFF'FF'FF);
    Label(std::string const& text, utils::Vec2f position, int zIndex = 0, uint32_t color = 0xFF'FF'FF);

    void setLabel(std::string const& newLabel);
    void setOutline(uint32_t color, float thickness = 1.0f);
    std::string& getText() { return m_text; }
    std::string const& getText() const { return m_text; }
    void draw() const override;

private:
    std::string m_text;

};

}
}