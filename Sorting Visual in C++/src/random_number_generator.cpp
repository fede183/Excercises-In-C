#include <cstdlib>
#include <ctime>
#include <iostream>

#ifndef RANDOM_HPP
#define RANDOM_HPP
unsigned int random_number_generator(unsigned int index) {
  srand((unsigned) time(0) + index);

  return (rand() % 99) + 1;
}
#endif