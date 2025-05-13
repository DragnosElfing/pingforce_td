#pragma once

#include "all.hpp"

namespace pftd {
namespace utils {

/*!
    Olyan osztályok, amelyek tárolóként (is) használhatók. Fontos: nem egy tárolót tartalmaznak, hanem azok maguk a tárolók (öröklés, nem kompozíció)!
    Ilyen például: `FollowPath`, `Inventory`.

    Megjegyzés: iterátorokat nem tartalmaz, de elérhető a `getContainer()`.
*/
template<typename T, typename C = std::vector<T*>>
class Container
{
public:
    Container() = default;
    virtual ~Container()
    {
        for(auto& elem : m_container) {
            delete elem;
        }
    }

    /**
    * @brief Új elem hozzáadása.
    *
    * @param elem A hozzáadni kívánt dolog.
    * @return Az imént hozzáadott dolog.
    */
    /*virtual*/ T* const append(T* elem)
    {
        m_container.push_back(elem);
        return elem;
    }

    /**
    * @brief A tároló mérete.
    *
    * @return A tároló elemeinek száma.
    */
    std::size_t size() const { return m_container.size(); }

    /**
    * @brief Konstans `m_container` getter.
    *
    * @return A tároló.
    */
    C const& getContainer() const { return m_container; }

private:
    /*! A tároló. */
    C m_container;

};

}
}
