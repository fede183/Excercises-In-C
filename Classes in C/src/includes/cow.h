#ifndef COW_H
#define COW_H
#include "animal.h"
typedef struct COW_STRUTC
{
    Animal* base;
} Cow;

Cow* new_cow();

#endif // !COW_H