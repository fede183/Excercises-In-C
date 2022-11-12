#include "color.h"

#ifndef PIECE_H
#define PIECE_H
struct Point
{
    int x, y;
    color point_color;
};
struct Piece
{
    Point positions[4];
};
#endif // PIECE_H