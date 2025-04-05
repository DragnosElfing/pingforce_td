#pragma once

#include <cmath>
#include <ostream>

namespace pftd {
namespace utils {

template<typename T>
struct Vec2
{
    T x, y;

    Vec2() {}
    Vec2(T x, T y): 
        x{x}, y{y}
    {}
    Vec2(Vec2 const& right):
        x{right.x}, y{right.y}
    {}

    static T distance(Vec2 const& v1, Vec2 const& v2)
    {
        return std::sqrt((v2.x-v1.x)*(v2.x-v1.x) + (v2.y-v1.y)*(v2.y-v1.y));
    }

    Vec2 operator+(Vec2 const& right) const
    {
        return {this->x + right.x, this->y + right.y};
    }

    Vec2 operator-(Vec2 const& right) const
    {
        return {this->x - right.x, this->y - right.y};
    }

    Vec2 operator/(T scalar) const
    {
        return {this->x / scalar, this->y / scalar};
    }
    Vec2 operator*(T scalar) const
    {
        return {this->x * scalar, this->y * scalar};
    }

    Vec2& operator=(Vec2 const& right)
    {
        if(&right != this) {
            this->x = right.x;
            this->y = right.y;
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, Vec2 const& vec)
    {
        out << "(" << vec.x << " " << vec.y << ")";
        return out;
    }
};

using Vec2i = Vec2<int>;
using Vec2f = Vec2<float>;

}
}