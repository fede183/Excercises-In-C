
#include "point.hpp"
#include "linked_list.hpp"
#include "piece.hpp"

#ifndef BOARD_HPP
#define BOARD_HPP
class Board
{
private:
    Linked_List<Linked_List<unsigned int>>* board_rows;
    unsigned int board_row_size;
    unsigned int board_column_size;
public:
    Board(const unsigned int board_row_size, const unsigned int board_column_size);
    ~Board();

    unsigned int** get_columns();

    void add_point(Point point);
    void add_piece(Piece* piece);

    bool has_point(Point point);
    bool has_colitions_bottom_or_remains(Piece* piece);
    bool has_colitions_bottom_and_top(Piece* piece);
    bool has_colitions_border_or_remains(Piece* piece);

    unsigned int delete_complete_lines();
    unsigned int get_row_quantity();
    unsigned int get_column_quantity(const unsigned int index);
};
#endif // BOARD_HPP