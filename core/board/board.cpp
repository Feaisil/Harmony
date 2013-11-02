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

std::ostream& operator<< (std::ostream& stream, const ::harmony::core::board::Board & board)
{
    stream << "{ balancePoint : "
           << board.balancePoint
           << "| size : "
           << board.size
           << " }";

    return stream;
}

}}} // namespaces

