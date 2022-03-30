
#include <iostream>

#include "../classes/point.hpp"
#include "../classes/board.hpp"
#include "../../Generic SFML Utils/src/linked_list.cpp"
#include "piece.cpp"

bool operator==(const PointForBoard& point1, const PointForBoard& point2)
{
    return point1.x == point2.x;
}

Board::Board(const unsigned int board_row_size, const unsigned int board_column_size) {
    this->board_rows = new Linked_List<Linked_List<PointForBoard>>();
    this->board_row_size = board_row_size;
    this->board_column_size = board_column_size;
}
Board::~Board() {
    delete board_rows;
}

PointForBoard** Board::get_columns()
{
    unsigned int size = this->board_rows->get_size();
    if (size > 0) {
        PointForBoard** columns = (PointForBoard**) malloc(sizeof(PointForBoard*) * size);
        Linked_List<PointForBoard>* rows = (Linked_List<PointForBoard>*) this->board_rows->get_all_values();
        for (unsigned int i = 0; i < size; i++) {
            PointForBoard* column = rows[i].get_all_values();
            columns[i] = column;
        }
        
        return columns;
    }
    
    return NULL;
}

void Board::add_point(Point point) {
    unsigned int x = point.x;
    unsigned int y = point.y;
    
    unsigned int size = this->board_rows->get_size();
    unsigned int real_y = this->board_row_size - 1 - y;
    if (real_y >= size) {
        unsigned int iterator_size = 1 + real_y - size;
        while (iterator_size > 0) {
            iterator_size--;
            Linked_List<PointForBoard>* new_row = new Linked_List<PointForBoard>();

            this->board_rows->push(*new_row);
        }
    } 

    PointForBoard pointForBoard;
    pointForBoard.x = x;
    pointForBoard.point_color = point.point_color; 
    
    this->board_rows->get_value(real_y)->push(pointForBoard);
}

void Board::add_piece(Piece* piece) {
    for (unsigned int i = 0; i < 4; i++) {
        this->add_point(piece->get_point(i));
    }
}

bool Board::has_point(Point point) {
    unsigned int x = point.x;
    unsigned int y = point.y;
    
    unsigned int size = this->board_rows->get_size();
    unsigned int real_y = this->board_row_size - 1 - y;
    if (real_y >= size) {
        return false;
    }

    PointForBoard pointForBoard;
    pointForBoard.x = x;
   
    return this->board_rows->get_value(real_y)->has_value(pointForBoard);
}

bool Board::has_colitions_bottom_or_remains(Piece* piece) {
    bool has_colitions_top = false;
    unsigned int board_row_size = this->board_row_size;
    for (unsigned int i = 0; i < 4; i++)
    {
        Point point = piece->get_point(i);
        has_colitions_top = has_colitions_top || 
        !(point.y < board_row_size) || this->has_point(point);
    }

    return has_colitions_top;
}

bool Board::has_colitions_bottom_and_top(Piece* piece) {
    bool has_colitions_top = false;
    int board_row_size = this->board_row_size;
    for (unsigned int i = 0; i < 4; i++)
    {
        Point point = piece->get_point(i);
        has_colitions_top = has_colitions_top || 
        (board_row_size <= point.y || this->has_point(point));
    }

    return has_colitions_top;
}

bool Board::has_colitions_border_or_remains(Piece* piece) {
    bool has_colitions_border_or_remains = false;
    for (unsigned int i = 0; i < 4; i++)
    {
        Point point = piece->get_point(i);
        has_colitions_border_or_remains = has_colitions_border_or_remains || 
        !(0 <= point.x && point.x < this->board_column_size) 
        || this->has_point(point);
    }

    return has_colitions_border_or_remains;
}

unsigned int Board::delete_complete_lines() {
    unsigned int size = this->board_rows->get_size();
    Linked_List<PointForBoard>* rows = this->board_rows->get_all_values();
    unsigned int quantity_lines_delete = 0;
    unsigned int i = 0, j = 0;
    while (i < size)
    {
        if (rows[i].get_size() == board_column_size) {
            this->board_rows->remove(i - j);
            quantity_lines_delete++;
            j++;
        }
        i++;
    }
    return quantity_lines_delete;
}

unsigned int Board::get_row_quantity() {
    return this->board_rows->get_size();
}

unsigned int Board::get_column_quantity(const unsigned int index) {
    return this->board_rows->get_value(index)->get_size();
}