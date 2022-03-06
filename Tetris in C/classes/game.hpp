#include "board.hpp"
#include "piece.hpp"
#include "config.hpp"

#ifndef GAME_HPP
#define GAME_HPP
class Game
{
private:
    Board* board;
    Piece* piece;
    Piece* old_piece;
    Piece* next_piece;
    int dx_count = 0, dy_count = 0;
    int score = 0, level = 0, complete_lines = 0;

public:
    Game();
    ~Game();
    void move_left();
    void move_right();
    void descend();

    void rotate();

    bool is_game_over();

    void clean_for_cycle();

    int get_score();
    int get_level();

    void check_state();
    
    int get_point_quantity();
    Point* get_all_points();
    Point* get_next_piece_points();
};
#endif // GAME_HPP