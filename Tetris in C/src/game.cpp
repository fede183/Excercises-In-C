#include "../classes/config.hpp"
#include "../classes/point.hpp"
#include "../classes/game.hpp"
#include "board.cpp"

Game::Game() {
    // Declare Board
    this->board = new Board(Config::complete_vertical_squares, Config::horizontal_squares);
    this->piece = new Piece();
    this->old_piece->copy(piece);
}
Game::~Game() {
    delete board;
    delete piece;
}
void Game::move_left() {
    dx = -1;
    dx_count -= dx_count == 0 ? 0 : 1;
    this->piece->move(-1);
    if (this->board->has_colitions_border_or_remains(this->piece)) 
        this->old_piece->copy(this->piece);
}

void Game::move_right() {
    dx = 1;
    dx_count += dx_count == Config::horizontal_squares ? 0 : 1;
    this->piece->move(1);
    if (this->board->has_colitions_border_or_remains(this->piece)) 
        this->old_piece->copy(this->piece);
}
void Game::descend() {
    this->dy = 1;
    this->dy_count += this->dy_count == Config::complete_vertical_squares ? 0 : 1;
    this->piece->descend(1);
}

void Game::rotate() {
    Point center_point = this->piece->get_center_point();
    for (int i = 0; i < 4; i++) {
        int rotate_x = this->piece->get_point(i).y - center_point.y;
        int rotate_y = this->piece->get_point(i).x - center_point.x;         
        this->piece->set_point(center_point.x - rotate_x, center_point.y + rotate_y, i);
    }
    if (this->dx_count == 0) {
        while (this->board->has_colitions_border_or_remains(this->piece)) {
            this->piece->move(1);
        }
        while (!this->piece->touching_zero_border()) {
            this->piece->move(-1);
        }
    }  
    if (this->dy_count == 0) {
        while (this->piece->has_colitions_top()) {
            this->piece->descend(1);
        }
        while (!this->piece->touching_zero_top()) {
            this->piece->descend(-1);
        }
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
    dx = 0, dy = 0;     
}
int Game::get_score() {
    return score;
}
int Game::get_level() {
    return level;
}

void Game::check_state() {
    if (this->dx == 0 && this->board->has_colitions_bottom_or_remains(this->piece)) {
        this->old_piece->copy(this->piece);
        this->board->add_piece(this->piece);
        // Check Board for complete lines
        int complete_lines_quantity = this->board->delete_complete_lines();
        this->score += Config::scores[complete_lines_quantity - 1];
        this->complete_lines += complete_lines_quantity;
        this->piece = new Piece();
        this->old_piece->copy(piece);
        this->dx_count = 0;
        this->dy_count = 0;
    }
}

int Game::get_row_quantity() {
    return this->board->get_row_quantity();
}
int Game::get_column_quantity(int index) {
    return this->board->get_column_quantity(index);
}
int** Game::get_all_points_board() {
    return this->board->get_columns();
}
Piece* Game::get_piece() {
    return this->piece;
}