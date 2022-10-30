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
    Point get_center_point(int board_column_size);
    Point get_point(const unsigned int index);
    void set_point(const unsigned int x, const unsigned int y, const unsigned int index);

    void move(const unsigned int dx);
    void descend(const unsigned int dy);
    
    bool has_colitions_top();
};
#endif // PIECE_HPP