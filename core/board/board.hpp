#pragma once

#include <memory>

#include "core/element.hpp"
#include "position.hpp"

namespace harmony{ namespace core{
namespace events{
class PureHarmony;
}
namespace board{

typedef Position BalancePoint;

class Board
{
public:

    /// Functions
public:
    Board(unsigned int size);
    /** Update a placement with an input element */
    void operator()(Position& position, common::Element element) const;
protected:
private:
    /// Members
public:
protected:
private:
    BalancePoint balancePoint;
    unsigned int size;

    friend class events::PureHarmony;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & BOOST_SERIALIZATION_NVP(balancePoint);
        ar & BOOST_SERIALIZATION_NVP(size);
    }
};
}}}
