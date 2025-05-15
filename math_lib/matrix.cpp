#include "matrix.h"
#include "vector_methods.h"
#include <iostream>
#include <vector>
#include <stdexcept>

Matrix::Matrix(int r, int c): ROWS(r), COLUMNS(c) {
  _matrix = std::vector<std::vector<int> > (r, std::vector<int>(c, 0));
}

void Matrix::print() {
  std::cout << "ROWS: " << this->ROWS << "\nCOLUMNS: " << this->COLUMNS << std::endl;
  for (std::vector<int> i : this->_matrix) {
    printVector(i);
  }
}

/**
* accessed via: _matrix(ROW, COLUMN)
*/
int& Matrix::operator() (int row, int col) {
  if (row >= this->ROWS || col >= this->COLUMNS) {
    throw std::invalid_argument("Row or Column were out of bounds");
  }
  return this->_matrix[row][col];
}

/**
* ### how to multiply two matrices
*
* given Ra and Ca
* given a row (ie, row 0),
* multiply row 0 by each col
*
* to multiply a row by a col,
* row 0[0] * col[0]
* +
* row 0[1] * col[1]
*
* do this for every row
* each sum of a row * col = an index of the product matrix
* row 0 * col 0 = product[0][0]
* row 0 * col 1 = product[0][1]
* ..
* row 3 * col 3 = product[3][3]
*
* ### how to know if two matrices cant multiply
* if num cols of matrix 0 != num rows of matrix 1
* ie, cant multiple a 2x3 by a 2x2
* _can_ multiply a 3x2 by a 2x1
*
* BAD
* | | |
* | | |
*
* | |
* | |
*
* GOOD
* | |
* | |
* | |
*
* | 
* |
*/

/**
* func multiply_matrices
* @input const struct matrix_s *A, *B
* @input_desc two pointers to the matrices to be multiplied
*
* @output const struct matrix_s
* @output_desc pointer to calculated product of input matrices. will be empty matrix, with R & C of 0 if the input matrices cant be multiplied together
*
* @desc
* first, check if we can multiply these matrices in the first place
* if A->C == B->R, then we can
* otherwise, return product->C & R = 0
*  
* height (num of rows, Product->R) of product matrix = A->R
* width (num of cols, Product->C) of product matrix = B->C
*  
* then, we multiply each row of A by each col of B
* dot product:
*   var product = 0
*     for (index in row)
*     product += row[index] * col[index]
*  
* each dot product becomes an index of the product matrix
* row 0 * col 0 = product[0][0]
* row 0 * col 1 = product[0][1]
*
*/

Matrix* Matrix::multiplyMatrices(const Matrix *left, const Matrix *right) {
  if (left->COLUMNS != right->ROWS) {
    //throw invalid arg: "instance columns does not equal input rows
    throw std::invalid_argument("left columns does not equal right rows");
  }
  Matrix *product = new Matrix(left->ROWS, right->COLUMNS);

  for (int i = 0; i < product->ROWS; i++) {
    for (int j = 0; j < product->COLUMNS; j++) {
      // here we calc dot product, for left->ROW[i] * right->COLUMN[j]
      // this product is inserted at product[i][j]
      for (int v = 0; v < left->COLUMNS /* can also be B->R */; v++) {
        // left[i][v]
        //  for the given row, [i], read every value, [v]
        // right[v][j]
        //  read every value, [v], for the given column, [j]
        product->_matrix[i][j] += left->_matrix[i][v] * right->_matrix[v][j];
      }
    }
  }
  return product;
}

/*
*
* func getDeterminant
*
* currently only implements a 2x2 matrix. throws invalid_argument if `this` does not have correct dimensions
* 
*/
int Matrix::getDeterminant() {
  if (this->ROWS != 2 || this->COLUMNS != 2) {
    throw std::invalid_argument("`this` matrix is not a 2x2 matrix");
  }

  // (0, 0 * 1, 1) - (1, 0 * 0, 1)
  return (this->_matrix[0][0] * this->_matrix[1][1]) - (this->_matrix[1][0] * this->_matrix[0][1]);
}

