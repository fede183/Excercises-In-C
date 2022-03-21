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
    Piece* backout_piece;
    Piece* next_piece;
    unsigned int score = 0, level = 0, complete_lines = 0;

public:
    Game();
    ~Game();
    void move_left();
    void move_right();
    void descend();

    void rotate();

    bool is_game_over();

    void clean_for_cycle();

    unsigned int get_score();
    unsigned int get_level();

    bool check_state();
    
    unsigned int get_point_quantity();
    Point* get_all_points();
    Point* get_next_piece_points();
};
#endif // GAME_HPP