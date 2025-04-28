#include "vector_methods.h"
#include <iostream>

void printVector(const std::vector<int> vec) {
  for (int i : vec) {
    std::cout << ' ' << i;
  }
  std::cout << std::endl;
}
