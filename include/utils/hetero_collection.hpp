#pragma once

#include "utils/logger.hpp"
#include <stdexcept>
#include <type_traits>
#include <vector>

namespace pftd {
namespace utils {
    
// TODO: turn this into "container"
template<typename T, typename C = std::vector<T>>
class HCollection
{
public:
    class iterator {};
    class const_iterator {};

    HCollection() = default;
    virtual ~HCollection()
    {
        if(std::is_pointer<typename C::value_type>::value) {
            // for(auto& obj : m_container) {
            //     delete obj;
            // }
        }
    }

    [[maybe_unused]]
    virtual T const append(T elem)
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

    std::size_t size() const { return m_container.size(); }
    C const& getContainer() const { return m_container; }

private:
    C m_container;
};

}
}