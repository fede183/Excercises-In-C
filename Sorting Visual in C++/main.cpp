#include <SFML/Graphics.hpp>

#include <stdio.h>
#include <stdlib.h>

#include "src/random_number_generator.cpp"

using namespace sf;

int main(int argc, char *argv[]) {

    unsigned int amount_numbers = 10; 
    unsigned int randoms[amount_numbers];

    for (size_t i = 0; i < amount_numbers; i++)
    {
        randoms[i] = random_number_generator(i);
    }

    unsigned int display_height = 600;

    RenderWindow window(VideoMode(1200, display_height), "Sorting!");

    RectangleShape rectangle;

    unsigned int i = 0, j = 1;
    float timer = 0, delay = 0;
    Clock clock;

    while (window.isOpen()) {
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
        
     
        window.display();
    }        

    
    return 0;
}