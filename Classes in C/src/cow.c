#include <stdlib.h>
#include "includes/cow.h"

Cow* new_cow() {
    Cow* cow = calloc(1, sizeof(struct COW_STRUTC));
    animal_construct("Vaca", (Animal*) cow, "Moohhh Moohhh");

    return cow;
}
