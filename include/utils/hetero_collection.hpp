#pragma once

#include <stdexcept>
#include <vector>

#include "utils/logger.hpp"

namespace pftd {
namespace utils {
    
template<typename T, typename C = std::vector<T*>>
class HCollection
{
public:
    class iterator {};
    class const_iterator {};

    HCollection() = default;
    ~HCollection()
    {
        for(auto& obj : m_container) {
            delete obj;
        }
    }

    [[maybe_unused]]
    T* const append(T* elem)
    {   
        try {
            m_container.push_back(elem);
        } catch(std::runtime_error err) {
            throw std::runtime_error{err.what()}; // bruh.
        }

        return elem;
    }

    template<typename Pred>
    void remove(Pred);

    inline std::size_t size() const { return m_container.size(); }

private:
    C m_container;
};

}
}