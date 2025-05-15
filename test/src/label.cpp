#include "mock_objects/mock_gui/label.hpp"

using namespace pftd_test::gr;

Label::Label(std::wstring const& label, int, unsigned int, uint32_t):
    m_text{std::to_string(*label.c_str())}
{

}

Label::Label(std::wstring const& label, int, unsigned int, utils::Vec2f position, int zIndex, uint32_t):
    Object{position, {}, zIndex},
    m_text{std::to_string(*label.c_str())}
{

}

void Label::setLabel(std::string const& newLabel)
{
    m_text = newLabel;
}

void Label::setOutline(uint32_t, float)
{
    where();
}

void Label::draw() const
{
    where();
}