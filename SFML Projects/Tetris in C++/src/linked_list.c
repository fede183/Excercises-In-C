#include <iostream>
#include <stdbool.h>  

#include "../classes/linked_list.h"


LinkedList* createList(size_t data_size) {
    LinkedList* newList = (LinkedList*) malloc(sizeof(LinkedList));

    newList->first = NULL;
    newList->last = NULL;
    newList->size = 0;
    newList->data_size = data_size;

    return newList;
}


void clean(LinkedList* list) {
    delete list->first;
    delete list->last;
    delete list;
}

void push(LinkedList* list, void* data) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    if (list->first == NULL) {
        list->first = new_node;
    } else if (list->last == NULL) {
        list->first->next = new_node;
        list->last = new_node;
    } else {
        list->last->next = new_node;
        list->last = new_node;
    }
    list->size++;
}


void remove(LinkedList* list, int index) {
    int size = list->size;
    Node* node_to_delete;
    if (index == 0) {
        node_to_delete = list->first;
        list->first = list->first->next;
        if (size == 2) {
            list->last = NULL;
        }
        
    } else {
        Node* iterator = list->first;
        
        for (int i = 0; i < index - 1; i++)
        {
            iterator = iterator->next;
        }
        
        if (size - 1 == index) {
            node_to_delete = list->last;
            list->last = iterator;
        } else {
            node_to_delete = iterator->next;
            iterator->next = iterator->next->next;
        }
    }
    
    delete node_to_delete;
    list->size--;
}


void* get_value(LinkedList* list, int index) {
    if (index == 0) {
        return list->first->data;
    } else if (index == list->size - 1) {
        return list->last->data;
    } else {
        Node* iterator = list->first;
        for (int i = 0; i < index; i++)
        {
            iterator = iterator->next;
        }
        return iterator->data;
    }
}


void* get_all_values(LinkedList* list) {
    Node* iterator = list->first;
    unsigned int size = list->size;
    void** values = (void**) malloc(sizeof(list->data_size) * size);
    unsigned int i = 0;
    while (iterator != NULL) {
        values[i] = iterator->data;
        i++;
        iterator = iterator->next;
    }
    return values;
}


bool has_value(LinkedList* list, void* value, bool (*compare) (void*, void*)) {
    Node* iterator = list->first;
    while (iterator != NULL)
    {
        if (compare(value, iterator->data)) 
            return true;
        iterator = iterator->next;
    }
    return false;
}