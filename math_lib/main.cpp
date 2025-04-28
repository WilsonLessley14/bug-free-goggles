#include <iostream>
#include "matrix.h"
#include "vector_methods.h"

int main () {
  Matrix m(10, 10);
  m.print();

  std::vector<int> left;
  std::vector<int> right;

  left.push_back(1);left.push_back(-2);left.push_back(3);
  right.push_back(4);right.push_back(5);right.push_back(6);

  std::vector<int> sum = addVectors(left, right);

  printVector(sum);

  std::cout << m[5][0];
  return 0;
}
