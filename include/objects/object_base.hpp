#pragma once

#include "all.hpp"

namespace pftd
{

/*! Programelemek. */
class Object : public sf::Drawable
{
public:
    Object() = default;
    
    /**
    * @brief
    *
    * @param position Pozíció koordinátái.
    * @param size Méret.
    * @param zIndex Z koordináta: "mélységi index."
    */
    Object(utils::Vec2f position, utils::Vec2f size, int zIndex = 0):
        zIndex{zIndex}, position{position}, size{size}
    {}

    Object(Object const&) = default;
    Object(Object&&) noexcept = default;
    
    virtual ~Object() = default;

    /**
    * @brief Objektum megjelenítése.
    *
    * @param target Hol legyen megjelenítve? Ez általában egy ablak.
    * @param states Render-eléshez szükséges egyéb állapotok.
    */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

    /*! Priority queue miatt szükséges segédosztály. */
    struct Compare
    {
        // bool operator()(Object const& o1, Object const& o2) const
        // {
        //     return o1.zIndex > o2.zIndex;
        // };

        bool operator()(Object const* o1, Object const* o2) const
        {
            if(!o1 || !o2) return false;
            return o1->zIndex > o2->zIndex;
            //return this->operator()(*o1, *o2);
        };
    };

protected:
    /*! Z koordináta. */
    int zIndex = 0;

    /*! Pozíció. */
    utils::Vec2f position;

    /*! Méret (szélesség x magasság). */
    utils::Vec2f size;

};

}