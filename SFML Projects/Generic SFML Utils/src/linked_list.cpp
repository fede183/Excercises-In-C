#include <iostream>

#include "../classes/node.hpp"
#include "../classes/linked_list.hpp"

template<class T>
Linked_List<T>::Linked_List() {
    this->first = NULL;
    this->last = NULL;
    this->size = 0;
}

template<class T>
Linked_List<T>::~Linked_List() {
    delete this->first;
    delete this->last;
}

template<class T>
unsigned int Linked_List<T>::get_size() {
    return this->size;
}

template<class T>
void Linked_List<T>::push(T data) {
    Node<T>* new_node = new Node<T>;
    new_node->data = data;
    new_node->next = NULL;
    if (this->first == NULL) {
        this->first = new_node;
    } else if (this->last == NULL) {
        this->first->next = new_node;
        this->last = new_node;
    } else {
        this->last->next = new_node;
        this->last = new_node;
    }
    this->size++;
}

template<class T>
void Linked_List<T>::remove(int index) {
    unsigned int size = this->size;
    Node<T>* node_to_delete;
    if (index == 0) {
        node_to_delete = this->first;
        this->first = this->first->next;
        if (size == 2) {
            this->last = NULL;
        }
        
    } else {
        Node<T>* iterator = this->first;
        
        for (int i = 0; i < index - 1; i++)
        {
            iterator = iterator->next;
        }
        
        if (size - 1 == index) {
            node_to_delete = this->last;
            this->last = iterator;
        } else {
            node_to_delete = iterator->next;
            iterator->next = iterator->next->next;
        }
    }
    
    delete node_to_delete;
    this->size--;
}

template<class T>
T* Linked_List<T>::get_value(int index) {
    if (index == 0) {
        return &(this->first->data);
    } else if (index == this->size - 1) {
        return &(this->last->data);
    } else {
        Node<T>* iterator = this->first;
        for (unsigned int i = 0; i < index; i++)
        {
            iterator = iterator->next;
        }
        return &(iterator->data);
    }
}

template<class T>
T* Linked_List<T>::get_all_values() {
    Node<T>* iterator = this->first;
    unsigned int size = this->size;
    T* values = (T*) malloc(sizeof(T) * size);
    unsigned int i = 0;
    while (iterator != NULL) {
        values[i] = iterator->data;
        i++;
        iterator = iterator->next;
    }
    return values;
}

template<class T>
bool Linked_List<T>::has_value(T value) {
    Node<T>* iterator = this->first;
    while (iterator != NULL)
    {
        if (value == iterator->data) 
            return true;
        iterator = iterator->next;
    }
    return false;
}