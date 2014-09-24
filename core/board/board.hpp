#pragma once

#include <memory>

#include "core/element.hpp"
#include "position.hpp"

namespace harmony{ namespace core{
namespace events{
class HarmoniousMeal;
class MoveAllTowardsElement;
class MovePlayerTowardsElement;
}
namespace board{

typedef Position BalancePoint;

class Board
{
public:

    /// Functions
public:
    Board( int size);
    /** Update a placement with an input element */
    void operator()(Position& position, common::Element element, bool negative = false) const;
    void moveToCenter(Position& position) const;
protected:
private:
    /// Members
public:
    const BalancePoint& getBalancePoint() const;
    int ComputeScore(const Position& position) const;
protected:
private:
    BalancePoint balancePoint;
    int size;

private:
    friend class events::HarmoniousMeal;
    friend class events::MoveAllTowardsElement;
    friend class events::MovePlayerTowardsElement;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int )
    {
        ar & BOOST_SERIALIZATION_NVP(balancePoint);
        ar & BOOST_SERIALIZATION_NVP(size);
    }
};
}}}
