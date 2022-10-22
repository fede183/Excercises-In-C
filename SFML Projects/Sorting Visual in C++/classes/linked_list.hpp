#include "node.hpp"

#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP
template<class T>
class Linked_List
{
private:
    Node<T>* first;
    Node<T>* last;
    unsigned int size;
public:
    Linked_List();
    ~Linked_List();

    unsigned int get_size();

    void push(T data);
    void remove(int index);

    T* get_value(int index);
    T* get_all_values();
    bool has_value(T value);
};
#endif // LINKED_LIST_HPP