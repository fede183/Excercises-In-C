#include <iterator>

#include "../classes/config.hpp"
#include "../classes/point.hpp"
#include "../classes/piece.hpp"

Piece::Piece() {
    int piece = rand() % 7;
    for (int i = 0; i < 4; i++)
    {
        int figure_position = Config::figures[piece][i]; 
        this->positions[i].x = figure_position % 2;
        this->positions[i].y = figure_position / 2;
    }
}
Piece::Piece(Point positions[4]) {
    for (int i = 0; i < 4; i++)
    {
        this->positions[i] = positions[i];
    }
}
Piece::~Piece() {}

void Piece::copy(Piece* copy) {
    //copy = new Piece(copy);
}

Point Piece::get_center_point() {
    return this->positions[1];
}
Point Piece::get_point(int index) {
    return this->positions[index];
}
void Piece::set_point(int x, int y, int index) {
    this->positions[index].x = x;
    this->positions[index].y = y;
}

void Piece::move(int dx) {
    //<-Move->
    if (dx != 0) 
        for (int i = 0; i < 4; i++) {
            this->positions[i].x += dx;
        }
}
void Piece::descend(int dy) {
    //|Move
    //V
    if (dy != 0) 
        for (int i = 0; i < 4; i++) {
            this->positions[i].y += dy;
        }
}

bool Piece::has_colitions_top() {
    bool has_colitions_top = false;
    for (int i = 0; i < 4; i++)
    {
        has_colitions_top = has_colitions_top || 
        !(0 <= this->positions[i].y);
    }
    return has_colitions_top;
}
bool Piece::touching_zero_border() {
    for (int i = 0; i < 4; i++)
    {
        if (this->positions[i].x == 0) {
            return true;
        }
    }
    return false;
}
bool Piece::touching_zero_top() {
    for (int i = 0; i < 4; i++)
    {
        if (this->positions[i].y == 0) {
            return true;
        }
    }
    return false;
}