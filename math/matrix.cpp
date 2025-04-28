#include "matrix.h"
#include <iostream>
#include <vector>

Matrix::Matrix(int r, int c): ROWS(r), COLUMNS(c) {
  _matrix = std::vector<std::vector<int> > (c, std::vector<int>(r, 0));
}

void Matrix::print() {
  std::cout << "ROWS: " << this->ROWS << "\nCOLUMNS: " << this->COLUMNS << std::endl;
  for (std::vector<int> i : this->_matrix) {
    for( int j : i ) {

      std::cout << " " << j;
    }
    std::cout << std::endl;
  }
}

/**
* accessed via: _matrix[ROW][COLUMN]
*/
std::vector<int> Matrix::operator[] (int row) {
  return this->_matrix[row];
}
