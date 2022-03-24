#include <iterator>

#include "../classes/config.hpp"
#include "../classes/point.hpp"
#include "../classes/piece.hpp"
#include "../classes/color.hpp"
#include "random_number_generator.cpp"

Piece::Piece() {
    unsigned int piece = random_number_generator();
    unsigned int colorInt = random_number_generator();
    color theColor = static_cast<color>(colorInt);

    for (unsigned int i = 0; i < 4; i++)
    {
        unsigned int figure_position = Config::figures[piece][i]; 
        this->positions[i].x = figure_position % 2;
        this->positions[i].y = figure_position / 2;
        this->positions[i].point_color = theColor;
    }
}
Piece::Piece(Point positions[4]) {
    for (unsigned int i = 0; i < 4; i++)
    {
        this->positions[i] = positions[i];
    }
}
Piece::~Piece() {}

void Piece::copy(Piece* copy) {
    for (unsigned int i = 0; i < 4; i++)
    {
        copy->positions[i] = this->positions[i];
    }
}

Point Piece::get_center_point() {
    return this->positions[1];
}
Point Piece::get_point(const unsigned int index) {
    return this->positions[index];
}
void Piece::set_point(const unsigned int x, const unsigned int y, const unsigned int index) {
    this->positions[index].x = x;
    this->positions[index].y = y;
}

void Piece::move(const unsigned int dx) {
    //<-Move->
    if (dx != 0) 
        for (unsigned int i = 0; i < 4; i++) {
            this->positions[i].x += dx;
        }
}
void Piece::descend(const unsigned int dy) {
    //|Move
    //V
    if (dy != 0) 
        for (unsigned int i = 0; i < 4; i++) {
            this->positions[i].y += dy;
        }
}

bool Piece::has_colitions_top() {
    bool has_colitions_top = false;
    for (unsigned int i = 0; i < 4; i++)
    {
        has_colitions_top = has_colitions_top || 
        !(0 <= this->positions[i].y);
    }
    return has_colitions_top;
}