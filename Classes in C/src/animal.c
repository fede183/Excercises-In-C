#include <stdio.h>
#include "includes/animal.h"

Animal* animal_construct(char* animalName, Animal* animal, char* speech) {
    animal->animalName = animalName;
    animal->speech = speech;
    animal->speek = animal_speek;

    return animal;
}

void animal_speek(Animal* animal) {
    printf("%s hace %s\n", animal->animalName, animal->speech);
}
