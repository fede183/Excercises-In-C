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
public:
    Game_Loop();
    ~Game_Loop();
    void render_game_over_window();
    void start();

};
#endif // GAME_HPP