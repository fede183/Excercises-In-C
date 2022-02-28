
#include <iterator>
#include "config.h"
#include "point.h"

class Piece
{
private:
    Point positions[4];
public:
    Piece() {
        int piece = rand() % 7;

        for (int i = 0; i < 4; i++)
        {
            int figure_position = Config::figures[piece][i]; 
            positions[i].x = figure_position % 2;
            positions[i].y = figure_position / 2;
        }
    }
    Piece(Point positions[4]) {
        for (int i = 0; i < 4; i++)
        {
            this->positions[i] = positions[i];
        }
    }
    ~Piece(){}

    void copy(Piece* copy) {
        Point copy_positions[4];
        std::copy(std::begin(positions), std::end(positions), std::begin(copy_positions));
        copy = new Piece(positions);
    };
    Point get_center_point() {
        return positions[1];
    }
    Point get_point(int index) {
        return positions[index];
    }
    void set_point(int x, int y, int index) {
        positions[index].x = x;
        positions[index].y = y;
    }

    void move(int dx) {
        //<-Move->
        if (dx != 0) 
            for (int i = 0; i < 4; i++) {
                positions[i].x += dx;
            }
    }

    void descend(int dy) {
        //|Move
        //V
        if (dy != 0) 
            for (int i = 0; i < 4; i++) {
                positions[i].y += dy;
            }
    }

    bool has_colitions_top() {
        bool has_colitions_top = false;

        for (int i = 0; i < 4; i++)
        {
            has_colitions_top = has_colitions_top || 
            !(0 <= positions[i].y);
        }

        return has_colitions_top;
    }

    bool touching_zero_border() {
        for (int i = 0; i < 4; i++)
        {
            if (positions[i].x == 0) {
                return true;
            }
        }

        return false;
    }

    bool touching_zero_top() {
        for (int i = 0; i < 4; i++)
        {
            if (positions[i].y == 0) {
                return true;
            }
        }

        return false;
    }

};
