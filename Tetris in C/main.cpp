#include <SFML/Graphics.hpp>
#include <time.h>
#include <algorithm>
#include <iterator>

using namespace sf;

//------
//|0|1|8|12|
//|2|3|9|13|
//|4|5|10|14|
//|6|7|11|15|
//------

int figures[7][4] = {
    0, 2, 4, 6, //I
    2, 4, 5, 7, //Z
    3, 4, 5, 6, //S
    2, 4, 6, 7, //L
    3, 4, 5, 7, //T
    4, 5, 6, 7, //O
    3, 5, 6, 7, //J
};

int figures_horizontal_size[7][2] = {
    1, 4, //I
    2, 3, //Z
    2, 3, //S
    2, 3, //L
    2, 3, //T
    2, 2, //O
    2, 3, //J
};

struct Point
{
    int x, y;
} position[4];

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

void descend(int dx) {
    //|Move
    //V
    for (int i = 0; i < 4; i++) {
        position[i].y += dx;
    }
}

bool has_colitions_border() {
    bool has_colitions_border = false;

    for (int i = 0; i < 4; i++)
    {
        has_colitions_border = has_colitions_border || 
        !(0 <= position[i].x && position[i].x < 18);
    }

    return has_colitions_border;
}

bool has_colitions_top() {
    bool has_colitions_top = false;

    for (int i = 0; i < 4; i++)
    {
        has_colitions_top = has_colitions_top || 
        !(0 <= position[i].y && position[i].y < 27);
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

const int display_width = 324; 
const int display_heigth = 486; 
const int square_sixe = 18; 



int main()
{
    RenderWindow window(VideoMode(display_width, display_heigth), "Tetris!");
    
    Texture texture;
    texture.loadFromFile("images/tiles.png");

    Sprite sprite(texture);
    
    sprite.setTextureRect(IntRect(0, 0, square_sixe, square_sixe));

    int piece = 0, dx = 0, dx_count = 0, dy_count = 0;
    bool rotate = false;

    // First Draw figure, one square at the time
    if (position[0].x == 0)
        for (int i = 0; i < 4; i++)
        {
            position[i].x = figures[piece][i] % 2;
            position[i].y = figures[piece][i] / 2;
        }


    while (window.isOpen())
    {
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
                        dx_count += dx_count == 18 ? 0 : 1;
                        break;
                    case Keyboard::Up:
                        rotate = true;
                        break;
                    default:
                        break;
                }
        

        window.clear(Color::White);

        Point old_position[4];
        copy(position, old_position);

        move(dx);

        // Check for border colitions
        if (has_colitions_border()) 
            copy(old_position, position);


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
                while (has_colitions_border()) {
                    move(1);
                }

                while (has_colitions_top()) {
                    descend(1);
                }

                while (!touching_zero_border()) {
                    move(-1);
                }
            }  

            if (dy_count == 0) {
                while (!touching_zero_top()) {
                    descend(-1);
                }
            }        
        }

        // Draw Figure
        for (int i = 0; i < 4; i++)
        {
            sprite.setPosition(position[i].x*square_sixe, position[i].y*square_sixe);
            window.draw(sprite);
        }
        

        dx = 0, rotate = false;
        

        window.display();
    }
    

    return 0;
}