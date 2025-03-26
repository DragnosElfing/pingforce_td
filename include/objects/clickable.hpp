#include <functional>

namespace pftd
{

class Clickable
{
public:
    virtual void setCallback(std::function<void()> callback) = 0;
    virtual void handleClick(int x, int y) = 0;

protected:
    std::function<void()> m_callback;

};

};