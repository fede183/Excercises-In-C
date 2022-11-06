#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(1000, 1000), "Pacman!");
    float timer = 0, delay = 0;
    Clock clock;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
            if (event.type == Event::Closed)
                window.close();

        window.clear(Color::Red);
        window.display();
    }

    return 0;
}