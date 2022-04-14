#include <SFML/Graphics.hpp>

#include <stdio.h>
#include <stdlib.h>

#include "../Generic SFML Utils/src/random_number_generator.cpp"
#include "../Generic SFML Utils/src/button.cpp"

using namespace sf;

bool large_selected = false;


void render_large_selector_message() {
    RenderWindow large_selector_message(VideoMode(500, 200), "Elegir largo!");
    
    Text text;
    Font font;

    if (!font.loadFromFile("fonts/textFont.ttf"))
        throw("Error al cargar la fuente");
    

    text.setCharacterSize(24);
    text.setStyle(Text::Bold);
    text.setFont(font);
    text.setFillColor(Color::Black);
    text.setPosition(25, 30);
    text.setString("Elegir largo de la muestra");

    Button accept_button("Aceptar", Vector2f(120, 80), Vector2f(120, 50), font);

    function<void(void)> acceptClickEvent = [&]() {
        large_selected = true;
        large_selector_message.close();
    };

    accept_button.setClickEvent(acceptClickEvent);


    while (large_selector_message.isOpen()) {
        Event event;
        while (large_selector_message.pollEvent(event)) {
            if (event.type == Event::Closed) {
                large_selector_message.close();
            }

            accept_button.update(event);
        }
        large_selector_message.clear(Color::Black);
        
        large_selector_message.draw(accept_button);
        large_selector_message.draw(text);
        large_selector_message.display();
    }        
}

int main(int argc, char *argv[]) {

    unsigned int amount_numbers = 10; 
    unsigned int randoms[amount_numbers];

    for (size_t i = 0; i < amount_numbers; i++)
    {
        randoms[i] = random_number_generator(1, 100, i);
    }

    unsigned int display_height = 600;

    RenderWindow window(VideoMode(1200, display_height), "Sorting!");

    RectangleShape rectangle;

    unsigned int i = 0, j = 1;
    float timer = 0, delay = 0;
    Clock clock;

    while (window.isOpen()) {
        if (large_selected) {
            delay = 3000;
            float time = clock.getElapsedTime().asSeconds();
            timer += time;
            
            window.clear();
            
                    
            // <--Tick-->
            if (timer > delay) {
                if (i < amount_numbers) {
                    if (randoms[j] < randoms[i]) {
                        unsigned int aux = randoms[i];
                        randoms[i] = randoms[j];
                        randoms[j] = aux;
                    }

                    j++;

                    if (j > amount_numbers) {
                        i++;
                        j = i + 1;
                    }
                }
                timer = 0;
            }
            
            
            for (size_t index = 0; index < amount_numbers; index++)
            {
                unsigned int random_elem = randoms[index];

                if (index == i) {
                    rectangle.setFillColor(Color::Yellow);
                } else if (index == j) {
                    rectangle.setFillColor(Color::Red);
                } else {
                    rectangle.setFillColor(Color::White);
                }


                rectangle.setSize(Vector2f(100, 10*random_elem));
                rectangle.setPosition(100*index, display_height - 10*random_elem);
        
                window.draw(rectangle);
            }
            
        } else {
            render_large_selector_message();
        }
        
        window.display();
    }        

    
    return 0;
}