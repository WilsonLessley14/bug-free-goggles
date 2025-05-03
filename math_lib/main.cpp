#include <iostream>
#include "matrix.h"
#include "vector_methods.h"

int main () {

  Matrix matrix1(2, 3);
  Matrix matrix2(3, 2);

  matrix1(0, 0) = 3;
  matrix1(1, 2) = 2;

  matrix2(0, 0) = 5;
  matrix2(2, 1) = 4;

  matrix1.print();
  matrix2.print();

  Matrix *matrix3 = Matrix::multiplyMatrices(&matrix1, &matrix2);

  std::cout << "\nproduct of above matrices: " << std::endl;
  matrix3->print();


  std::vector<int> left;
  std::vector<int> right;

  left.push_back(1);left.push_back(-2);left.push_back(3);
  right.push_back(4);right.push_back(5);right.push_back(6);

  std::vector<int> sum = addVectors(left, right);

  printVector(sum);

  std::cout << "sum, scaled by 4:" << std::endl;

  printVector(scaleVector(4, sum));

  return 0;
}
