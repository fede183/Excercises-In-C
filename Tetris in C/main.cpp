#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <time.h>
#include <algorithm>
#include <iterator>

#include "classes/config.hpp"
#include "classes/point.hpp"
#include "src/game.cpp"

#include "src/random_number_generator.cpp"

using namespace sf;


void draw_sprite(unsigned int x, unsigned int y, Sprite &sprite) {
    if (Config::invisible_squares <= y) {
        sprite.setPosition(x*Config::square_sixe, (y + Config::header_squares)*Config::square_sixe);
    }
}

int main()
{
    // Window, Textures, Sprites, Text, Music
    RenderWindow window(VideoMode(Config::display_width + Config::display_side_block_width, Config::display_heigth), "Tetris!");
    
    Texture texturePoint;
    texturePoint.loadFromFile("images/tiles.png");

    Sprite sprite(texturePoint);
    unsigned int color_of_texture = random_number_generator();

    sprite.setTextureRect(IntRect(18*color_of_texture, 0, 18, 18));
    float scale = (float)Config::square_sixe / 18;
    sprite.setScale(scale, scale);
    
    RectangleShape rectangle_header;
    rectangle_header.setSize(Vector2f(Config::display_width, Config::display_header));
    rectangle_header.setFillColor(Color(190, 180, 180));

    RectangleShape rectangle_side_block;
    rectangle_side_block.setSize(Vector2f(Config::display_side_block_width, Config::display_header + Config::display_heigth));
    rectangle_side_block.setFillColor(Color(190, 180, 180));
    rectangle_side_block.setPosition(Config::display_width, 0);

    RectangleShape rectangle_next_piece;
    rectangle_next_piece.setSize(Vector2f(Config::display_next_piece_block_width, Config::display_next_piece_block_heigth));
    rectangle_next_piece.setFillColor(Color::Black);
    rectangle_next_piece.setPosition(Config::display_next_piece_block_position_x, Config::display_next_piece_block_position_y);

    Text textScore;
    Font font;

    //if (!font.loadFromFile("fonts/textFont.ttf"))
    //    throw("Error al cargar la fuente");
    

    textScore.setCharacterSize(24);
    textScore.setStyle(Text::Bold);
    textScore.setFont(font);
    textScore.setFillColor(Color::Black);

    float timer = 0, delay = 0;
    Clock clock;

    Music music;

    //if (!music.openFromFile("sounds/theme.wav"))
    //    throw("Error al cargar la música");
    
    music.setLoop(true);
    music.play();

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
        
        window.clear(Color::Black);
                
        window.draw(rectangle_header);
        window.draw(rectangle_side_block);
        window.draw(rectangle_next_piece);
        
        // <--Tick-->
        if (timer > delay) {
            game->descend();
            timer = 0;
        }

        bool needs_new_piece = game->check_state();

        if (needs_new_piece) {
            color_of_texture = random_number_generator();

            sprite.setTextureRect(IntRect(18*color_of_texture, 0, 18, 18));
        }

        if (!game->is_game_over()) {
            // Draw Points
            Point* points = game->get_all_points();
            int point_quantity = game->get_point_quantity();

            for (int i = 0; i < point_quantity; i++)
            {
                draw_sprite(points[i].x, points[i].y, sprite);
                window.draw(sprite);
            }

            delete points;
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

        Point* points = game->get_next_piece_points();
        for (int i = 0; i < 4; i++)
        {
            draw_sprite(points[i].x, points[i].y, sprite);
            window.draw(sprite);
        }

        delete points;

        window.display();
    }
    
    delete game;

    return 0;
}