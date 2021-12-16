#include <stdlib.h>
#include "includes/cat.h"

Cat* new_cat() {
    Cat* cat = calloc(1, sizeof(struct CAT_STRUTC));
    animal_construct("Gato", (Animal*) cat, "Miauu");

    return cat;
}
