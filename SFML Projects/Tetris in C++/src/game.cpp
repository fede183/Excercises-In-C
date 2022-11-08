#include "../classes/config.hpp"
#include "../classes/piece.hpp"
#include "../classes/game.hpp"
#include "board.cpp"

Game::Game() {
    // Declare Board
    this->board = new Board(Config::complete_vertical_squares, Config::horizontal_squares);
    this->piece = createPiece();
    this->backout_piece = createPiece();
    copy(this->piece, this->backout_piece);
    this->next_piece = createPiece();
}

Game::~Game() {
    delete board;
    delete piece;
}

void Game::move_left() {
    for (int i = 0; i < 4; i++) {
        this->piece->positions[i].x -= 1;
    }
    if (this->board->has_colitions_border_or_remains(this->piece)) 
        copy(this->backout_piece, this->piece);
}

void Game::move_right() {
    for (int i = 0; i < 4; i++) {
        this->piece->positions[i].x += 1;
    }
    if (this->board->has_colitions_border_or_remains(this->piece)) 
        copy(this->backout_piece, this->piece);
}

void Game::descend() {
    for (int i = 0; i < 4; i++) {
        this->piece->positions[i].y += 1;
    }
}

void Game::rotate() {
    Point center_point = this->piece->positions[1];
    printf("center point is: (%i, %i)\n", center_point.x, center_point.y);
    for (int i = 0; i < 4; i++) {
        unsigned int rotate_x = this->piece->positions[i].y - center_point.y;
        unsigned int rotate_y = this->piece->positions[i].x - center_point.x;         
        this->piece->positions[i].x = center_point.x - rotate_x;
        this->piece->positions[i].y =  center_point.y + rotate_y;

    }

    while (this->board->has_colitions_border_or_remains(this->piece)) {
        this->move_right();
    }

    while (has_colitions_top(this->piece)) {
        this->descend();
    }

}

bool Game::is_game_over() {
    return this->board->get_row_quantity() > Config::vertical_squares;
}

void Game::clean_for_cycle() {
    if (complete_lines > 10 && level < 4) {
        complete_lines -= 10;
        level += 1;
    } 
    copy(this->piece, this->backout_piece);
}

unsigned int Game::get_score() {
    return score;
}
unsigned int Game::get_level() {
    return level;
}

void Game::check_state() {
    if (this->board->has_colitions_bottom_or_remains(this->piece)) {
        copy(this->backout_piece, this->piece);
        this->board->add_piece(this->piece);
        // Check Board for complete lines
        int complete_lines_quantity = this->board->delete_complete_lines();
        this->score += Config::scores[complete_lines_quantity - 1];
        this->complete_lines += complete_lines_quantity;

        // Get next piece
        copy(this->next_piece, this->piece);
        this->next_piece = createPiece();
        copy(this->piece, this->backout_piece);
    }
}

unsigned int Game::get_point_quantity() {
    unsigned int point_quantity = 0;
    unsigned int row_len = this->board->get_row_quantity();
    for (unsigned int j = 0; j < row_len; j++)
    {
        unsigned int column_len = this->board->get_column_quantity(j);
        point_quantity += column_len;
    }

    return point_quantity + 4;
}

Point* Game::get_next_piece_points() {

    Point* points = (Point*) malloc(sizeof(Point) * 4);

    for (unsigned int i = 0; i < 4; i++)
    {
        Point point = this->next_piece->positions[i];

        point.x += Config::next_piece_block_position_x + 2;
        point.y += Config::next_piece_block_position_y;

        points[i] = point;
    }

    return points;
}

Point* Game::get_all_points() {

    PointForBoard** columns = this->board->get_columns();
    unsigned int row_len = this->board->get_row_quantity();
    unsigned int point_quantity = this->get_point_quantity();
    Point* points = (Point*) malloc(sizeof(Point) * point_quantity);

    unsigned int point_index = 0;
    for (unsigned int j = 0; j < row_len; j++)
    {
        PointForBoard* column = columns[j];
        unsigned int column_len = this->board->get_column_quantity(j);
        for (unsigned int i = 0; i < column_len; i++)
        {
            unsigned int real_y = Config::complete_vertical_squares - 1 - j;
            unsigned int position_x = column[i].x;
            unsigned int position_y = real_y;
            color point_color = column[i].point_color;

            Point point;
            point.x = position_x;
            point.y = position_y;
            point.point_color = point_color;
            
            points[point_index] = point;

            point_index++;
        }

        delete column;
    }

    delete columns;

    for (unsigned int i = 0; i < 4; i++)
    {
        points[i + point_index] = this->piece->positions[i];
    }

    return points;
}