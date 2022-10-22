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
    Texture* texturePoint;
    Font* font;
    Music* music;
public:
    Game_Loop(Texture* texturePoint, Font* font, Music* music);
    ~Game_Loop();
    void render_game_over_window();
    void start();

};
#endif // GAME_LOOP_HPP