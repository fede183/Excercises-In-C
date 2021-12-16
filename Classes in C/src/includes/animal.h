#ifndef ANIMAL_H
#define ANIMAL_H
typedef struct ANIMAL_STRUTC
{
    char* animalName;
    char* speech;
    void* (*speek)(struct ANIMAL_STRUTC* self);
    
} Animal;

Animal* animal_construct(char* animalName, Animal* animal, char* speech);

void animal_speek(Animal* animal);

#endif // !ANIMAL_H