#include <iostream>
#include "matrix.h"
#include "vector_methods.h"

int main () {

  Matrix matrix1(2, 2), matrix2(2, 2), expected(2, 2);

  matrix1(0, 0) = 3;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 5;
  matrix1(1, 1) = 12;

  matrix2(0, 0) = 0;
  matrix2(0, 1) = -1;
  matrix2(1, 0) = 1;
  matrix2(1, 1) = 0;

  expected(0, 0) = 1;
  expected(0, 1) = -1;
  expected(1, 0) = 1;
  expected(1, 1) = 0;

  matrix1.print();
  matrix2.print();

  Matrix *matrix3 = Matrix::multiplyMatrices(&matrix1, &matrix2);

  std::cout << "\ncomposition of above matrices: " << std::endl;
  matrix3->print();

  std::cout << "\nshould equal: " << std::endl;
  expected.print();

  std::cout << "\n\nmatrix 1: \n";
  matrix1.print();
  std::cout << "\nmatrix 1 determinant: " << matrix1.getDeterminant() << std::endl;
  return 0;
}
