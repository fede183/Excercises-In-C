#include "board.hpp"
#include "piece.hpp"
#include "config.h"

#ifndef GAME_HPP
#define GAME_HPP
struct Game
{
    Board* board;
    Piece* piece;
    Piece* backout_piece;
    Piece* next_piece;
    unsigned int score, level, complete_lines;
};
#endif // GAME_HPP