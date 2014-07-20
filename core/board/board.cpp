#include "board.hpp"

namespace harmony{ namespace core{ namespace board{

Board::Board(unsigned int size):
    size(size)
{}

void Board::operator()(Position& position, common::Element element) const
{
    // if placement is not at end move
    if(position.index < size)
    {
        position(element);
    }
}
const BalancePoint &Board::getBalancePoint() const
{
    return balancePoint;
}

}}} // namespaces

