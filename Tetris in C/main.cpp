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

const int display_width = 324; 
const int display_heigth = 480; 
const int square_sixe = 18; 

int main()
{
    RenderWindow window(VideoMode(display_width, display_heigth), "Tetris!");
    
    Texture texture;
    texture.loadFromFile("images/tiles.png");

    Sprite sprite(texture);
    
    sprite.setTextureRect(IntRect(0, 0, square_sixe, square_sixe));

    int piece = 4, dx = 0;
    bool rotate = false;

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
                        break;
                    case Keyboard::Right:
                        dx = 1;
                        break;
                    case Keyboard::Up:
                        rotate = true;
                        break;
                    default:
                        break;
                }
        

        window.clear(Color::White);

        Point old_position[4];
        std::copy(std::begin(position), std::end(position), std::begin(old_position)) ;

        //<-Move->
        for (int i = 0; i < 4; i++) {
            position[i].x += dx;
        }


        //Rotate
        if (rotate) {
            Point center_point = position[1];
            for (int i = 0; i < 4; i++) {
                int rotate_x = position[i].y - center_point.y;
                int rotate_y = position[i].x - center_point.x;         
                position[i].x = center_point.x - rotate_x; 
                position[i].y = center_point.y + rotate_y;
            }
        }
        

        //Draw figure, one square at the time
        if (position[0].x == 0)
            for (int i = 0; i < 4; i++)
            {
                position[i].x = figures[piece][i] % 2;
                position[i].y = figures[piece][i] / 2;
            }

        bool has_collitions_border = false;

        for (int i = 0; i < 4; i++)
        {
            has_collitions_border = has_collitions_border || 
            !(0 <= position[i].x && position[i].x < 18);
        }
 

        if (has_collitions_border) 
            copy(old_position, position);

        for (int i = 0; i < 4; i++)
        {
            sprite.setPosition(position[i].x*square_sixe, position[i].y*square_sixe);
            window.draw(sprite);
        }
        

        dx = 0, rotate = false, has_collitions_border = false;
        

        window.display();
    }
    

    return 0;
}