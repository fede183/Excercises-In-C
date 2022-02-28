#include "point.hpp"

#ifndef PIECE_HPP
#define PIECE_HPP
class Piece
{
private:
    Point positions[4];
public:
    Piece();
    Piece(Point positions[4]);
    ~Piece();

    void copy(Piece*);
    Point get_center_point();
    Point get_point(int index);
    void set_point(int x, int y, int index);

    void move(int dx);
    void descend(int dy);
    
    bool has_colitions_top();
    bool touching_zero_border();
    bool touching_zero_top();
};
#endif // PIECE_HPP