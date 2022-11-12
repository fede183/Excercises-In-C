#include "color.hpp"

#ifndef PIECE_HPP
#define PIECE_HPP
struct Point
{
    int x, y;
    color point_color;
};
struct Piece
{
    Point positions[4];
};
#endif // PIECE_HPP