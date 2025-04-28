#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

class Matrix {
  int ROWS, COLUMNS;
  std::vector<std::vector<int> > _matrix;
public:
  Matrix(int r, int c);
  void print();
  std::vector<int> operator[] (int row);
};

#endif
