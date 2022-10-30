#include "src/game_loop.cpp"


int main()
{
    Texture texturePoint;

    if (!texturePoint.loadFromFile("images/tiles.png"))
        throw("Texture load error");

    Font font;

    if (!font.loadFromFile("fonts/textFont.ttf"))
        throw("Error al cargar la fuente");

    Music music;

    //if (!music.openFromFile("sounds/theme.wav"))
    //    throw("Error al cargar la música");

    Game_Loop* game_loop = new Game_Loop(&texturePoint, &font, &music);

    game_loop->start();
    
    delete game_loop;

    return 0;
}