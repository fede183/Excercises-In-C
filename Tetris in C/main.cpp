#include <SFML/Graphics.hpp>
#include <time.h>
#include <algorithm>
#include <iterator>
#include "point.h"
#include "board.cpp"


using namespace sf;

//------
//|0|1|8|12|
//|2|3|9|13|
//|4|5|10|14|
//|6|7|11|15|
//------

int figures[7][4] = {
    0, 2, 4, 6, //I
    1, 2, 3, 4, //Z
    0, 2, 3, 5, //S
    0, 2, 4, 5, //L
    1, 2, 3, 5, //T
    0, 1, 2, 3, //O
    1, 3, 4, 5, //J
};

const int square_sixe = 10; 
const int horizontal_squares = 10;
const int vertical_squares = 27;
const int display_width = square_sixe*horizontal_squares; 
const int display_heigth = square_sixe*vertical_squares; 

Board* board;

// <Position Functions>

Point position[4];

void copy(Point (&point_to_copy)[4], Point (&copy)[4]) {
    std::copy(std::begin(point_to_copy), std::end(point_to_copy), std::begin(copy));
};

void move(int dx) {
    //<-Move->
    if (dx != 0) 
        for (int i = 0; i < 4; i++) {
            position[i].x += dx;
        }
}

void descend(int dy) {
    //|Move
    //V
    if (dy != 0) 
        for (int i = 0; i < 4; i++) {
            position[i].y += dy;
        }
}

bool has_colitions_top() {
    bool has_colitions_top = false;

    for (int i = 0; i < 4; i++)
    {
        has_colitions_top = has_colitions_top || 
        !(0 <= position[i].y);
    }

    return has_colitions_top;
}

bool touching_zero_border() {
    for (int i = 0; i < 4; i++)
    {
        if (position[i].x == 0) {
            return true;
        }
    }

    return false;
}

bool touching_zero_top() {
    for (int i = 0; i < 4; i++)
    {
        if (position[i].y == 0) {
            return true;
        }
    }

    return false;
}

void draw_sprite(int x, int y, Sprite &sprite) {
    sprite.setPosition(x*square_sixe, y*square_sixe);
}
// </Position Functions>

int main()
{
    RenderWindow window(VideoMode(display_width, display_heigth), "Tetris!");
    
    Texture texturePoint;
    texturePoint.loadFromFile("images/tiles.png");

    // Texture textureFrame;
    // textureFrame.loadFromFile("images/frame.png");

    // Texture textureBackground;
    // textureBackground.loadFromFile("images/background.png");

    Sprite sprite(texturePoint);
    
    sprite.setTextureRect(IntRect(0, 0, square_sixe, square_sixe));

    //Sprite frame(textureFrame), background(textureBackground);

    int dx = 0, dy = 0, dx_count = 0, dy_count = 0;
    bool rotate = false;
    bool new_piece = true;

    board = new Board(vertical_squares, horizontal_squares);

    float timer = 0, delay = 0.3;
    Clock clock;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event event;
        while (window.pollEvent(event))
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::KeyPressed)
                switch (event.key.code)
                {
                    case Keyboard::Left:
                        dx = -1;
                        dx_count -= dx_count == 0 ? 0 : 1;
                        break;
                    case Keyboard::Right:
                        dx = 1;
                        dx_count += dx_count == horizontal_squares ? 0 : 1;
                        break;
                    case Keyboard::Up:
                        rotate = true;
                        break;
                    case Keyboard::Down:
                        dy = 1;
                        dy_count += dy_count == vertical_squares ? 0 : 1;
                        break;
                    default:
                        break;
                }
        

        window.clear(Color::White);
        
        // Generate new piece
        if (new_piece) {
            int piece = rand() % 7;

            for (int i = 0; i < 4; i++)
            {
                position[i].x = figures[piece][i] % 2;
                position[i].y = figures[piece][i] / 2;
            }
            new_piece = false;
            dx_count = 0;
            dy_count = 0;
        }
        
        Point old_position[4];
        copy(position, old_position);

        // Rotate
        if (rotate) {
            Point center_point = position[1];

            for (int i = 0; i < 4; i++) {
                int rotate_x = position[i].y - center_point.y;
                int rotate_y = position[i].x - center_point.x;         
                position[i].x = center_point.x - rotate_x; 
                position[i].y = center_point.y + rotate_y;
            }

            if (dx_count == 0) {
                while (board->has_colitions_border_or_remains(position)) {
                    move(1);
                }

                while (!touching_zero_border()) {
                    move(-1);
                }
            }  

            if (dy_count == 0) {
                while (has_colitions_top()) {
                    descend(1);
                }

                while (!touching_zero_top()) {
                    descend(-1);
                }
            }        
        }

        move(dx);

        if (board->has_colitions_border_or_remains(position)) 
            copy(old_position, position);

        descend(dy);

        // <--Tick-->
        if (timer > delay) {
            descend(1);
            dy_count += 1;
            timer = 0;
        }

        // If is not moving to the sides and there is colitions in botton or ramains
        // Ask for new piece and save old one in board
        if (dx == 0 && board->has_colitions_bottom_or_remains(position)) {
            copy(old_position, position);
            board->add_piece(position);
            new_piece = true;
            // Check Board for complete lines
            board->delete_complete_lines();
        } else {
            // Draw Figure
            for (int i = 0; i < 4; i++)
            {
                draw_sprite(position[i].x, position[i].y, sprite);
                window.draw(sprite);
            }
        }

        if (board->get_row_quantity() <= vertical_squares) {
            // Draw Board
            int** columns = board->get_columns();
            int row_len = board->get_row_quantity();
            for (int j = 0; j < row_len; j++)
            {
                int* column = columns[j];
                int column_len = board->get_column_quantity(j);
                for (int i = 0; i < column_len; i++)
                {
                    int real_y = vertical_squares - 1 - j;
                    int position_x = column[i]*square_sixe;
                    int position_y = real_y*square_sixe;
                    draw_sprite(position_x, position_y, sprite);
                    window.draw(sprite);
                }
            }

            delete columns;
        } else {

        }
    

        dx = 0, dy = 0, rotate = false;
        
        //window.draw(frame);
        window.display();
    }
    

    return 0;
}