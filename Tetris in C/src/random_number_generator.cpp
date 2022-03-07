#include <cstdlib>
#include <ctime>
#include <iostream>

#ifndef RANDOM_HPP
#define RANDOM_HPP
int random_number_generator() {
  srand((unsigned) time(0));

  return rand() % 7;
}
#endif