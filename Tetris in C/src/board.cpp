
#include <iostream>

#include "../classes/point.hpp"
#include "../classes/board.hpp"
#include "linked_list.cpp"
#include "piece.cpp"

Board::Board(int board_row_size, int board_column_size) {
    this->board_rows = new Linked_List<Linked_List<int>>();
    this->board_row_size = board_row_size;
    this->board_column_size = board_column_size;
}
Board::~Board() {
    delete board_rows;
}

int** Board::get_columns()
{
    int size = this->board_rows->get_size();
    if (size > 0) {
        int** columns = (int**) malloc(sizeof(int*) * size);
        Linked_List<int>* rows = (Linked_List<int>*) this->board_rows->get_all_values();
        for (int i = 0; i < size; i++) {
            int* column = rows[i].get_all_values();
            columns[i] = column;
        }
        
        return columns;
    }
    
    return NULL;
}

void Board::add_point(Point point) {
    int x = point.x;
    int y = point.y;
    
    int size = this->board_rows->get_size();
    int real_y = this->board_row_size - 1 - y;
    if (real_y >= size) {
        int iterator_size = 1 + real_y - size;
        while (iterator_size > 0) {
            iterator_size--;
            Linked_List<int>* new_row = new Linked_List<int>();

            this->board_rows->push(*new_row);
        }
    } 
    
    this->board_rows->get_value(real_y)->push(x);
}

void Board::add_piece(Piece* piece) {
    for (int i = 0; i < 4; i++) {
        this->add_point(piece->get_point(i));
    }
}

bool Board::has_point(Point point) {
    int x = point.x;
    int y = point.y;
    
    int size = this->board_rows->get_size();
    int real_y = this->board_row_size - 1 - y;
    if (real_y >= size) {
        return false;
    }
   
    return this->board_rows->get_value(real_y)->has_value(x);
}

bool Board::has_colitions_bottom_or_remains(Piece* piece) {
    bool has_colitions_top = false;
    int board_row_size = this->board_row_size;
    for (int i = 0; i < 4; i++)
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
    for (int i = 0; i < 4; i++)
    {
        Point point = piece->get_point(i);
        has_colitions_top = has_colitions_top || 
        (board_row_size <= point.y || this->has_point(point));
    }

    return has_colitions_top;
}

bool Board::has_colitions_border_or_remains(Piece* piece) {
    bool has_colitions_border_or_remains = false;
    for (int i = 0; i < 4; i++)
    {
        Point point = piece->get_point(i);
        has_colitions_border_or_remains = has_colitions_border_or_remains || 
        !(0 <= point.x && point.x < this->board_column_size) 
        || this->has_point(point);
    }

    return has_colitions_border_or_remains;
}

int Board::delete_complete_lines() {
    int size = this->board_rows->get_size();
    Linked_List<int>* rows = this->board_rows->get_all_values();
    int quantity_lines_delete = 0;
    int i = 0, j = 0;
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

int Board::get_row_quantity() {
    return this->board_rows->get_size();
}

int Board::get_column_quantity(int index) {
    return this->board_rows->get_value(index)->get_size();
}