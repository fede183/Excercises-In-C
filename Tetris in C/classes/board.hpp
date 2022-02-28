
#include "point.hpp"
#include "linked_list.hpp"
#include "piece.hpp"

#ifndef BOARD_HPP
#define BOARD_HPP
class Board
{
private:
    Linked_List<Linked_List<int>>* board_rows;
    int board_row_size;
    int board_column_size;
public:
    Board(int board_row_size, int board_column_size);
    ~Board();

    int** get_columns();

    void add_point(Point point);
    void add_piece(Piece* piece);

    bool has_point(Point point);
    bool has_colitions_bottom_or_remains(Piece* piece);
    bool has_colitions_bottom_and_top(Piece* piece);
    bool has_colitions_border_or_remains(Piece* piece);

    int delete_complete_lines();
    int get_row_quantity();
    int get_column_quantity(int index);
};
#endif // BOARD_HPP