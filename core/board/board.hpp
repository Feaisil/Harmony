#pragma once

#include <memory>
#include "core/common.hpp"
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
    friend std::ostream& operator<< (std::ostream& stream, const Board & board);
};
}}}