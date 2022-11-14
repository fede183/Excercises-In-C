#include <stdlib.h>
#include "node.h"

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct LinkedList
{
    size_t size;
    size_t data_size;
    struct Node* first;
    struct Node* last;
} LinkedList;

#endif // LINKED_LIST_H