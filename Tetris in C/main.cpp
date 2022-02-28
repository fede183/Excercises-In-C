#include <SFML/Graphics.hpp>
#include <time.h>
#include <algorithm>
#include <iterator>
#include "src/piece.cpp"
#include "src/board.cpp"
#include "src/config.h"

using namespace sf;


Board* board;

Piece* piece;

void draw_sprite(int x, int y, Sprite &sprite) {
    if (Config::invisible_squares <= y) {
        sprite.setPosition(x*Config::square_sixe, (y + Config::header_squares)*Config::square_sixe);
    }
}

int main()
{
    RenderWindow window(VideoMode(Config::display_width, Config::display_heigth), "Tetris!");
    
    Texture texturePoint;
    texturePoint.loadFromFile("images/tiles.png");

    Sprite sprite(texturePoint);
    
    sprite.setTextureRect(IntRect(0, 0, 18, 18));
    float scale = (float)Config::square_sixe / 18;
    sprite.setScale(scale, scale);
    
    RectangleShape rectangle_header(Vector2f(Config::display_width, Config::display_header));
    rectangle_header.setFillColor(Color(190, 180, 180));

    Text textScore;
    Font font;

    if (!font.loadFromFile("fonts/textFont.ttf"))
        throw("Error al cargar la fuente");
    

    textScore.setCharacterSize(24);
    textScore.setStyle(Text::Bold);
    textScore.setFont(font);
    textScore.setFillColor(Color::Black);
    
    int score = 0, level = 0, complete_lines = 0;

    int dx = 0, dy = 0, dx_count = 0, dy_count = 0;
    bool rotate = false;
    bool new_piece = true;


    board = new Board(Config::complete_vertical_squares, Config::horizontal_squares);

    float timer = 0, delay = 0;
    Clock clock;

    while (window.isOpen())
    {
        delay = Config::delays_for_level[level];
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
                        dx_count += dx_count == Config::horizontal_squares ? 0 : 1;
                        break;
                    case Keyboard::Up:
                        rotate = true;
                        break;
                    case Keyboard::Down:
                        dy = 1;
                        dy_count += dy_count == Config::complete_vertical_squares ? 0 : 1;
                        break;
                    default:
                        break;
                }
        
        window.clear(Color::White);
                
        window.draw(rectangle_header);
        
        // Generate new piece
        if (new_piece) {
            piece = new Piece();
            new_piece = false;
            dx_count = 0;
            dy_count = 0;
        }
        
        Piece* old_piece;
        piece->copy(old_piece);

        // Rotate
        if (rotate) {
            Point center_point = piece->get_center_point();

            for (int i = 0; i < 4; i++) {
                int rotate_x = piece->get_point(i).y - center_point.y;
                int rotate_y = piece->get_point(i).x - center_point.x;         
                piece->set_point(center_point.x - rotate_x, center_point.y + rotate_y, i);
            }

            if (dx_count == 0) {
                while (board->has_colitions_border_or_remains(piece)) {
                    piece->move(1);
                }

                while (!piece->touching_zero_border()) {
                    piece->move(-1);
                }
            }  

            if (dy_count == 0) {
                while (piece->has_colitions_top()) {
                    piece->descend(1);
                }

                while (!piece->touching_zero_top()) {
                    piece->descend(-1);
                }
            }        
        }

        piece->move(dx);

        if (board->has_colitions_border_or_remains(piece)) 
            old_piece->copy(piece);

        piece->descend(dy);

        // <--Tick-->
        if (timer > delay) {
            piece->descend(1);
            dy_count += 1;
            timer = 0;
        }

        // If is not moving to the sides and there is colitions in botton or ramains
        // Ask for new piece and save old one in board
        if (dx == 0 && board->has_colitions_bottom_or_remains(piece)) {
            old_piece->copy(piece);
            board->add_piece(piece);
            new_piece = true;
            // Check Board for complete lines
            int complete_lines_quantity = board->delete_complete_lines();
            score += Config::scores[complete_lines_quantity - 1];
            complete_lines += complete_lines_quantity;
        } else {
            // Draw Figure
            for (int i = 0; i < 4; i++)
            {
                draw_sprite(piece->get_point(i).x, piece->get_point(i).y, sprite);
                window.draw(sprite);
            }
        }

        if (board->get_row_quantity() <= Config::vertical_squares) {
            // Draw Board
            int** columns = board->get_columns();
            int row_len = board->get_row_quantity();
            for (int j = 0; j < row_len; j++)
            {
                int* column = columns[j];
                int column_len = board->get_column_quantity(j);
                for (int i = 0; i < column_len; i++)
                {
                    int real_y = Config::complete_vertical_squares - 1 - j;
                    int position_x = column[i];
                    int position_y = real_y;
                    draw_sprite(position_x, position_y, sprite);
                    window.draw(sprite);
                }
            }

            delete columns;
        } else {
            window.close();
        }
        

        if (complete_lines > 10 && level < 4) {
            complete_lines -= 10;
            level += 1;
        } 

        textScore.setPosition(25, 30);
        textScore.setString("Puntaje: " + std::to_string(score));
        window.draw(textScore);

        textScore.setPosition(25, 60);
        textScore.setString("Nivel: " + std::to_string(level));
        window.draw(textScore);

        dx = 0, dy = 0, rotate = false; 
        
        window.display();
    }
    

    return 0;
}