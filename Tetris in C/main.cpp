#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <time.h>
#include <algorithm>
#include <iterator>

#include "classes/config.hpp"
#include "classes/piece.hpp"
#include "src/game.cpp"

using namespace sf;


void draw_sprite(int x, int y, Sprite &sprite) {
    if (Config::invisible_squares <= y) {
        sprite.setPosition(x*Config::square_sixe, (y + Config::header_squares)*Config::square_sixe);
    }
}

int main()
{
    // Window, Textures, Sprites, Text, Music
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

    float timer = 0, delay = 0;
    Clock clock;

    // Music music;

    // if (!music.openFromFile("sounds/theme.mp3"))
    //     throw("Error al cargar la música");
    
    // music.setLoop(true);
    // music.play();

    // Declare Game
    Game* game = new Game();

    while (window.isOpen())
    {
        delay = Config::delays_for_level[game->get_level()];
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
                        game->move_left();
                        break;
                    case Keyboard::Right:
                        game->move_right();
                        break;
                    case Keyboard::Up:
                        game->rotate();
                        break;
                    case Keyboard::Down:
                        game->descend();
                        break;
                    default:
                        break;
                }
        
        window.clear(Color::White);
                
        window.draw(rectangle_header);
        
        // <--Tick-->
        if (timer > delay) {
            game->descend();
            timer = 0;
        }

        game->check_state();

        if (!game->is_game_over()) {
            // Draw Piece
            Piece* piece = game->get_piece();
            for (int i = 0; i < 4; i++)
            {
                draw_sprite(piece->get_point(i).x, piece->get_point(i).y, sprite);
                window.draw(sprite);
            }
            // Draw Board
            int** columns = game->get_all_points_board();
            int row_len = game->get_row_quantity();
            for (int j = 0; j < row_len; j++)
            {
                int* column = columns[j];
                int column_len = game->get_column_quantity(j);
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

        game->clean_for_cycle();

        textScore.setPosition(25, 30);
        textScore.setString("Puntaje: " + std::to_string(game->get_score()));
        window.draw(textScore);

        textScore.setPosition(25, 60);
        textScore.setString("Nivel: " + std::to_string(game->get_level()));
        window.draw(textScore);


        window.display();
    }
    
    delete game;

    return 0;
}