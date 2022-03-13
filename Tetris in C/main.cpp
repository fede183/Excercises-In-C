#include "src/game_loop.cpp"


int main()
{
    Game_Loop* game_loop = new Game_Loop();

    game_loop->start();
    
    delete game_loop;

    return 0;
}