#include "includes/cat.h"
#include "includes/cow.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {

    Animal* zoo[] = {(Animal*)new_cow(), (Animal*)new_cat()};

    int zooSize = sizeof zoo / sizeof zoo[0];

    for (size_t i = 0; i < zooSize; i++)
    {
        zoo[i]->speek(zoo[i]);

        free(zoo[i]);
    }
    
    return 0;
}