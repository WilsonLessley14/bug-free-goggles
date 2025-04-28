#include <iostream>
#include "matrix.h"

int main () {
  Matrix m(10, 10);
  m.print();

  std::cout << m[5][0];
  return 0;
}
