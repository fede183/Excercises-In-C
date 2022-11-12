#include "linked_list.hpp"
#include "piece.h"
#include "color.h"

#ifndef BOARD_HPP
#define BOARD_HPP

struct PointForBoard
{
    int x;
    color point_color;
};

struct Board
{
    Linked_List<Linked_List<PointForBoard>>* board_rows;
    int board_row_size;
    int board_column_size;
};
#endif // BOARD_HPP