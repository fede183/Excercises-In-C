#include <cstdlib>
#include <ctime>
#include <iostream>

#ifndef RANDOM_HPP
#define RANDOM_HPP
unsigned int random_number_generator(unsigned int min, unsigned int max, unsigned int index = 0) {
  srand((unsigned) time(0) + index);

  return (rand() % (max - 1)) + min;
}
#endif