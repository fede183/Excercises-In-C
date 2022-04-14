#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <functional>

#include "../classes/config.hpp"
#include "../classes/game_loop.hpp"

#include "../../Generic SFML Utils/src/button.cpp"


Game_Loop::Game_Loop() {
    this->window = new RenderWindow(VideoMode(Config::display_width + Config::display_side_block_width, Config::display_heigth), "Tetris!");
    this->game = new Game();
}

Game_Loop::~Game_Loop() {
    delete this->window;
    delete this->lost_message;
    delete this->game;
}

void Game_Loop::render_game_over_window() {
    this->lost_message = new RenderWindow(VideoMode(Config::display_lost_message_width, Config::display_lost_message_heigth), "Game Over!");
    
    Text text;
    Font font;

    if (!font.loadFromFile("../fonts/textFont.ttf"))
        throw("Error al cargar la fuente");
    

    text.setCharacterSize(24);
    text.setStyle(Text::Bold);
    text.setFont(font);
    text.setFillColor(Color::Black);
    text.setPosition(25, 30);
    text.setString("Game Over!");

    Button accept_button("Aceptar", Vector2f(120, 80), Vector2f(120, 50), font);

    function<void(void)> acceptClickEvent = [&]() {
        this->lost_message->close();
        delete this->game;
        this->game = new Game();
    };

    accept_button.setClickEvent(acceptClickEvent);

    Button cancel_button("Cancelar", Vector2f(260, 80), Vector2f(120, 50), font);

    function<void(void)> cancelClickEvent = [&]() {
        this->lost_message->close();
        this->window->close();
    };

    cancel_button.setClickEvent(cancelClickEvent);

    while (this->lost_message->isOpen()) {
        Event event;
        while (this->lost_message->pollEvent(event)) {
            if (event.type == Event::Closed) {
                this->lost_message->close();
                this->window->close();
            }

            accept_button.update(event);
            cancel_button.update(event);
        }
        this->lost_message->clear(Color::Black);
        
        this->lost_message->draw(accept_button);
        this->lost_message->draw(cancel_button);
        this->lost_message->draw(text);
        this->lost_message->display();
    }        
}

using namespace std;

void draw_sprite(const unsigned int x, const unsigned int y, color point_color, Sprite& sprite) {
    if (Config::invisible_squares <= y) {
        sprite.setTextureRect(IntRect(18*point_color, 0, 18, 18));
        sprite.setPosition(x*Config::square_sixe, (y + Config::header_squares)*Config::square_sixe);
    }
}

void Game_Loop::start() {
    Texture texturePoint;

    if (!texturePoint.loadFromFile("../images/tiles.png"))
        throw("Error al cargar la textura");
    

    Sprite sprite(texturePoint);

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

    if (!font.loadFromFile("../fonts/textFont.ttf"))
        throw("Error al cargar la fuente");
    

    textScore.setCharacterSize(24);
    textScore.setStyle(Text::Bold);
    textScore.setFont(font);
    textScore.setFillColor(Color::Black);

    float timer = 0, delay = 0;
    Clock clock;

    Music music;

    if (!music.openFromFile("../sounds/theme.wav"))
        throw("Error al cargar la música");
    
    music.setLoop(true);
    music.play();

    while (this->window->isOpen())
    {
        delay = Config::delays_for_level[this->game->get_level()];
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event event;
        while (this->window->pollEvent(event))
            if (event.type == Event::Closed)
                this->window->close();
            else if (event.type == Event::KeyPressed)
                switch (event.key.code)
                {
                    case Keyboard::Left:
                        this->game->move_left();
                        break;
                    case Keyboard::Right:
                        this->game->move_right();
                        break;
                    case Keyboard::Up:
                        this->game->rotate();
                        break;
                    case Keyboard::Down:
                        this->game->descend();
                        break;
                    default:
                        break;
                }
            
   

        this->window->clear(Color::Black);

        this->window->draw(rectangle_header);
        this->window->draw(rectangle_side_block);
        this->window->draw(rectangle_next_piece);
        
        // <--Tick-->
        if (timer > delay) {
            this->game->descend();
            timer = 0;
        }

        bool needs_new_piece = this->game->check_state();

        if (!this->game->is_game_over()) {
            // Draw Points
            Point* points = this->game->get_all_points();
            int point_quantity = this->game->get_point_quantity();

            for (unsigned int i = 0; i < point_quantity; i++)
            {
                draw_sprite(points[i].x, points[i].y, points[i].point_color, sprite);
                this->window->draw(sprite);
            }

            delete points;
        } else {
            render_game_over_window();
        }

        this->game->clean_for_cycle();

        textScore.setPosition(25, 30);
        textScore.setString("Puntaje: " + std::to_string(this->game->get_score()));
        this->window->draw(textScore);

        textScore.setPosition(25, 60);
        textScore.setString("Nivel: " + std::to_string(this->game->get_level()));
        this->window->draw(textScore);

        Point* points = this->game->get_next_piece_points();
        for (unsigned int i = 0; i < 4; i++)
        {
            draw_sprite(points[i].x, points[i].y, points[i].point_color, sprite);
            this->window->draw(sprite);
        }

        delete points;

        this->window->display();
    }
}