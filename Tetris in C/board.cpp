
#include <iostream>
#include "point.h"
#include "linked_list.cpp"


class Board
{
private:
    LinkedList<LinkedList<int>>* board_rows;
    int board_row_size;
    int board_column_size;
public:
    Board(int board_row_size, int board_column_size) {
        this->board_rows = new LinkedList<LinkedList<int>>();
        this->board_row_size = board_row_size;
        this->board_column_size = board_column_size;
    }
    ~Board() {
        delete board_rows;
    }
    int** get_columns()
    {
        int size = this->board_rows->get_size();

        if (size > 0) {
            int** columns = (int**) malloc(sizeof(int*) * size);

            LinkedList<int>* rows = (LinkedList<int>*) this->board_rows->get_all_values();

            for (int i = 0; i < size; i++) {
                int* column = rows[i].get_all_values();

                columns[i] = column;
            }
            
            //delete rows;

            return columns;
        }
        
        return NULL;
    }
    void add_point(Point point) {
        int x = point.x;
        int y = point.y;
        
        int size = this->board_rows->get_size();
        int real_y = this->board_row_size - 1 - y;

        if (real_y >= size) {
            int iterator_size = 1 + real_y - size;

            while (iterator_size > 0) {
                iterator_size--;

                LinkedList<int>* new_row = new LinkedList<int>();
 
                this->board_rows->push(*new_row);
            }
        } 
        
        this->board_rows->get_value(real_y)->push(x);
    }
    void add_piece(Point (&piece)[4]) {

        for (int i = 0; i < 4; i++) {
            this->add_point(piece[i]);
        }

    }
    bool has_point(Point point) {
        int x = point.x;
        int y = point.y;
        
        int size = this->board_rows->get_size();
        int real_y = this->board_row_size - 1 - y;

        if (real_y >= size) {
            return false;
        }

        return this->board_rows->get_value(real_y)->has_value(x);
    }
    bool has_colitions_bottom_or_remains(Point (&piece)[4]) {
        bool has_colitions_top = false;

        int board_row_size = this->board_row_size;
        for (int i = 0; i < 4; i++)
        {
            Point point = piece[i];
            has_colitions_top = has_colitions_top || 
            !(point.y < board_row_size) || this->has_point(point);
        }

        return has_colitions_top;
    }
    bool has_colitions_bottom_and_top(Point (&piece)[4]) {
        bool has_colitions_top = false;
        int board_row_size = this->board_row_size;

        for (int i = 0; i < 4; i++)
        {
            Point point = piece[i];
            has_colitions_top = has_colitions_top || 
            (board_row_size <= point.y || this->has_point(point));
        }

        return has_colitions_top;
    }
    bool has_colitions_border_or_remains(Point (&piece)[4]) {
        bool has_colitions_border_or_remains = false;

        for (int i = 0; i < 4; i++)
        {
            Point point = piece[i];
            has_colitions_border_or_remains = has_colitions_border_or_remains || 
            !(0 <= point.x && point.x < this->board_column_size) 
            || this->has_point(point);
        }

        return has_colitions_border_or_remains;
    }
    int delete_complete_lines() {
  
        int size = this->board_rows->get_size();
        int board_row_size = this->board_row_size;
        LinkedList<int>* rows = this->board_rows->get_all_values();

        int quantity_lines_delete = 0;
        for (int i = 0; i < size; i++)
        {
            if (rows[i].get_size() == board_column_size) {
                this->board_rows->remove(i);
                quantity_lines_delete++;
            }
        }

        return quantity_lines_delete;
    }
    int get_row_quantity() {
        return this->board_rows->get_size();
    }
    int get_column_quantity(int index) {
        return this->board_rows->get_value(index)->get_size();
    }
};