#include "color.hpp"

#ifndef PIECE_HPP
#define PIECE_HPP
struct Point
{
    unsigned int x, y;
    color point_color;
};
struct Piece
{
    Point positions[4];
};
#endif // PIECE_HPP