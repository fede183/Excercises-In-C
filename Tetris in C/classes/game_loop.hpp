#include <SFML/Graphics.hpp>
#include "../src/game.cpp"
#include "config.hpp"

using namespace sf;

#ifndef GAME_LOOP_HPP
#define GAME_LOOP_HPP
class Game_Loop
{
private:
    Game* game;
    RenderWindow* window;
    RenderWindow* lost_message;
    int score = 0, level = 0, complete_lines = 0;

public:
    Game_Loop();
    ~Game_Loop();
    void render_game_over_window();
    void start();

};
#endif // GAME_HPP