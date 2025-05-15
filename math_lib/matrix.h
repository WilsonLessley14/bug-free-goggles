#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

class Matrix {
  int ROWS, COLUMNS;
  std::vector<std::vector<int> > _matrix;
public:
  Matrix(int r, int c);
  void print();
  int& operator() (int row, int col);
  static Matrix* multiplyMatrices(const Matrix *left, const Matrix *right);
  int getDeterminant();
};

#endif
