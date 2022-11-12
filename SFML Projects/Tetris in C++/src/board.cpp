
#include <iostream>

#include "../classes/board.hpp"
#include "linked_list.cpp"
#include "piece.c"

bool operator==(const PointForBoard& point1, const PointForBoard& point2)
{
    return point1.x == point2.x;
}

Board* createBoard(const unsigned int board_row_size, const unsigned int board_column_size) {
    Board* newBoard = (Board*) malloc(sizeof(Board));

    newBoard->board_rows = new Linked_List<Linked_List<PointForBoard>>();
    newBoard->board_row_size = board_row_size;
    newBoard->board_column_size = board_column_size;

    return newBoard;
}

PointForBoard** get_columns(Board* board)
{
    unsigned int size = board->board_rows->get_size();
    if (size > 0) {
        PointForBoard** columns = (PointForBoard**) malloc(sizeof(PointForBoard*) * size);
        Linked_List<PointForBoard>* rows = (Linked_List<PointForBoard>*) board->board_rows->get_all_values();
        for (unsigned int i = 0; i < size; i++) {
            PointForBoard* column = rows[i].get_all_values();
            columns[i] = column;
        }
        
        return columns;
    }
    
    return NULL;
}

void add_point(Board* board, Point point) {
    unsigned int x = point.x;
    unsigned int y = point.y;
    
    unsigned int size = board->board_rows->get_size();
    unsigned int real_y = board->board_row_size - 1 - y;
    if (real_y >= size) {
        unsigned int iterator_size = 1 + real_y - size;
        while (iterator_size > 0) {
            iterator_size--;
            Linked_List<PointForBoard>* new_row = new Linked_List<PointForBoard>();

            board->board_rows->push(*new_row);
        }
    } 

    PointForBoard pointForBoard;
    pointForBoard.x = x;
    pointForBoard.point_color = point.point_color; 
    
    board->board_rows->get_value(real_y)->push(pointForBoard);
}

void add_piece(Board* board, Piece* piece) {
    for (unsigned int i = 0; i < 4; i++) {
        add_point(board, piece->positions[i]);
    }
}

bool has_point(Board* board, Point point) {
    unsigned int x = point.x;
    unsigned int y = point.y;
    
    unsigned int size = board->board_rows->get_size();
    unsigned int real_y = board->board_row_size - 1 - y;
    if (real_y >= size) {
        return false;
    }

    PointForBoard pointForBoard;
    pointForBoard.x = x;
   
    return board->board_rows->get_value(real_y)->has_value(pointForBoard);
}

bool has_colitions_bottom_or_remains(Board* board, Piece* piece) {
    bool has_colitions_top = false;
    int board_row_size = board->board_row_size;
    for (unsigned int i = 0; i < 4; i++)
    {
        Point point = piece->positions[i];
        has_colitions_top = has_colitions_top || 
        !(point.y < board_row_size) || has_point(board, point);
    }

    return has_colitions_top;
}

bool has_colitions_bottom_and_top(Board* board, Piece* piece) {
    bool has_colitions_top = false;
    int board_row_size = board->board_row_size;
    for (unsigned int i = 0; i < 4; i++)
    {
        Point point = piece->positions[i];
        has_colitions_top = has_colitions_top || 
        (board_row_size <= point.y || has_point(board, point));
    }

    return has_colitions_top;
}

bool has_colitions_border_or_remains(Board* board, Piece* piece) {
    bool has_colitions_border_or_remains = false;
    for (unsigned int i = 0; i < 4; i++)
    {
        Point point = piece->positions[i];
        has_colitions_border_or_remains = has_colitions_border_or_remains || 
        !(0 <= point.x && point.x < board->board_column_size) 
        || has_point(board, point);
    }

    return has_colitions_border_or_remains;
}

unsigned int delete_complete_lines(Board* board) {
    unsigned int size = board->board_rows->get_size();
    Linked_List<PointForBoard>* rows = board->board_rows->get_all_values();
    unsigned int quantity_lines_delete = 0;
    unsigned int i = 0, j = 0;
    while (i < size)
    {
        if (rows[i].get_size() == board->board_column_size) {
            board->board_rows->remove(i - j);
            quantity_lines_delete++;
            j++;
        }
        i++;
    }
    return quantity_lines_delete;
}

unsigned int get_row_quantity(Board* board) {
    return board->board_rows->get_size();
}

unsigned int get_column_quantity(Board* board, const unsigned int index) {
    return board->board_rows->get_value(index)->get_size();
}
