#ifndef CAT_H
#define CAT_H
#include "animal.h"
typedef struct CAT_STRUTC
{
    Animal* base;
} Cat;

Cat* new_cat();

#endif // !CAT_H