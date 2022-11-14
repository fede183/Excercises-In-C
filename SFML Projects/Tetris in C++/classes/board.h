#include "linked_list.h"
#include "color.h"

#ifndef BOARD_H
#define BOARD_H
struct Board
{
    struct LinkedList* board_rows;
    int board_row_size;
    int board_column_size;
};
#endif // BOARD_H