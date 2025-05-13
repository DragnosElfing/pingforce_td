#pragma once

#include <cmath>
#include <iostream>

namespace pftd {
namespace utils {

/*! sf::Vector2 helyett használt matematikai vektor implementáció. */
template<typename T>
struct Vec2
{
    /*! X koordináta. */
    T x;

    /*! Y koordináta. */
    T y;

    Vec2() {}
    Vec2(T x, T y):
        x{x}, y{y}
    {}
    Vec2(Vec2 const& right):
        x{right.x}, y{right.y}
    {}

    /**
    * @brief Két vektor végpontja közti euklideszi távolság.
    *
    * @param v1 Egyik vektor.
    * @param v2 Másik vektor.
    * @return A távolság.
    */
    static float distance(Vec2 const& v1, Vec2 const& v2)
    {
        return std::sqrt((v2.x-v1.x)*(v2.x-v1.x) + (v2.y-v1.y)*(v2.y-v1.y));
    }

    /**
    * @brief Vektor normalizálása.
    *
    * Ez a metódus nem módosítja a Vec2-t, hanem egy újat hoz létre belőle.
    *
    * @return Egy új, normalizált Vec2.
    */
    Vec2 normalize() const
    {
        return *this / Vec2::distance(*this, {0, 0});
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
    bool operator==(Vec2 other) const
    {
        return this->x == other.x && this->y == other.y;
    }
    bool operator!=(Vec2 other) const
    {
        return !(this == other);
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
        out << vec.x << " " << vec.y;
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Vec2& vec)
    {
        in >> vec.x >> vec.y;
        return in;
    }
};

// Az SFML is ilyet csinál.
using Vec2i = Vec2<int>;
using Vec2f = Vec2<float>;

}
}
