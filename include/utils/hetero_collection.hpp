#pragma once

#include "all.hpp"

namespace pftd {
namespace utils {

/*! Olyan osztályok, amelyek tárolóként (is) használhatók. */
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
    virtual T* const append(T* elem)
    { 
        try {
            m_container.push_back(elem);
        } catch(std::runtime_error err) {
            throw std::runtime_error{err.what()}; // TODO: ezt ne így, nincs sok értelme
        }

        return elem;
    }

    // ? Nem biztos, hogy kelleni fog bármikor is.
    // template<typename Pred>
    // void remove(Pred);

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