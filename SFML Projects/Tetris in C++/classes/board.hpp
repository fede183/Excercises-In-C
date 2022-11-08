#include "linked_list.hpp"
#include "piece.hpp"
#include "color.hpp"

#ifndef BOARD_HPP
#define BOARD_HPP

struct PointForBoard
{
    unsigned int x;
    color point_color;
};

struct Board
{
    Linked_List<Linked_List<PointForBoard>>* board_rows;
    unsigned int board_row_size;
    unsigned int board_column_size;
};
#endif // BOARD_HPP